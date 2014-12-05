#ifndef ZL_LRUCACHE_H
#define ZL_LRUCACHE_H
#include <list>
#include <map>
#include <hash_map>
#include "thread/Mutex.h"

template<typename Key, typename Value, typename LockType = zl::thread::Mutex>
class LruCache
{
public:
    explicit LruCache(size_t capacity): capacity_(capacity)
    {
    }

    ~LruCache()
    {
        clear();
    }

public:
    void reset()
    {
        clear();
    }

    bool get(const Key& key, Value& value)
    {
        zl::thread::MutexLocker locker(mutex_);
        typename MAP::iterator iter = keyIndex_.find(key);
        if(iter != keyIndex_.end())
        {
            valueList_.splice(valueList_.begin(), valueList_, iter->second);
            iter->second = valueList_.begin();    //��������

            value = iter->second->second;
            return true;
        }
        return false;
    }

    //ͬ�ϣ����������������ֱ�ӷ���Ĭ��ֵ�� TODO������ֱ�ӽ�Ĭ��ֵ���뵽������
    Value getOrDefault(const Key& key, const Value& default_value = Value())
    {
        Value value;
        if(get(key, value))
            return value;
        return default_value;
    }

    //����cache�� �����������£�����ֱ�Ӵ���
    bool put(const Key& key, const Value& value)
    {
        zl::thread::MutexLocker locker(mutex_);
        typename MAP::iterator miter = keyIndex_.find(key);
        if(miter != keyIndex_.end()) //����
        {
            if(miter->second->second == value)  //����ȣ�ֱ�ӷ���
                return true;
            removeWithHolder(key);   //���Ƴ�
        }

        valueList_.push_front(std::make_pair(key, value));    //���»���

        typename LIST::iterator liter = valueList_.begin();
        keyIndex_[key] = liter;            //���·�������

        if(keyIndex_.size() > capacity_)   //�Ƿ���
        {
            liter = valueList_.end();
            --liter;
            removeWithHolder(liter->first);
        }
        return true;
    }

    bool remove(const Key& key)
    {
        zl::thread::MutexLocker locker(mutex_);
        return removeWithHolder(key);
    }

    bool hasKey(const Key& key) const
    {
        zl::thread::MutexLocker locker(mutex_);
        return keyIndex_.find(key) != keyIndex_.end();
    }

    size_t size() const
    {
        zl::thread::MutexLocker locker(mutex_);
        return valueList_.size();
    }

    size_t capacity() const
    {
        return capacity_;
    }

    bool isEmpty() const
    {
        zl::thread::MutexLocker locker(mutex_);
        return valueList_.empty();
    }

    bool isFull() const
    {
        zl::thread::MutexLocker locker(mutex_);
        return keyIndex_.size() == capacity_;
    }

private:
    void clear()
    {
        zl::thread::MutexLocker locker(mutex_);
        valueList_.clear();
        keyIndex_.clear();
    }

    bool removeWithHolder(const Key& key)  //ע��˴����Ժ���Ը�Ϊ����remove���valueֵ
    {
        typename MAP::iterator iter = keyIndex_.find(key);
        if(iter == keyIndex_.end())
            return false;
        valueList_.erase(iter->second);
        keyIndex_.erase(iter);
        return true;
    }

private:
    typedef std::list<std::pair<Key, Value> >       LIST;
    typedef std::hash_map<Key, typename LIST::iterator>  MAP;

    LIST                   valueList_;
    MAP                    keyIndex_;
    size_t                 capacity_;
    mutable LockType       mutex_;
};

#endif /* ZL_LRUCACHE_H */