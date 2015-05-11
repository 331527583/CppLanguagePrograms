#ifndef ZL_LRUCACHE_H
#define ZL_LRUCACHE_H
#include <list>
#include <map>
#include <hash_map>
#include "thread/Mutex.h"

template<typename Key, typename Value, class LockType = zl::thread::NullMutex>
class LruCache
{
public:
    explicit LruCache(size_t capacity) : capacity_(capacity), size_(0)
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
        zl::thread::LockGuard<LockType> lock(mutex_);
        typename MAP::iterator iter = keyIndex_.find(key);
        if(iter != keyIndex_.end())
        {
            valueList_.splice(valueList_.begin(), valueList_, iter->second);
            //iter->second = valueList_.begin();    //��������, �Ǳ���
            assert(iter->second == valueList_.begin());

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
        zl::thread::LockGuard<LockType> lock(mutex_);
        typename MAP::iterator miter = keyIndex_.find(key);
        if(miter != keyIndex_.end()) //����
        {
            // �����˸�key�ķ���˳���Ƿ���Ҫ����Ӧ��������ȷ����
            valueList_.splice(valueList_.begin(), valueList_, miter->second);
            miter->second->second = value;
        }
        else
        {
            if (size_ < capacity_)     // insert new one
            {
                valueList_.push_front(std::make_pair(key, value));
                keyIndex_[key] = valueList_.begin();
                size_++;
            }
            else      // ɾ�����ٷ��ʵ�Ԫ��
            {
                //��˫������list���޸ľ��Բ�����ʹԭ�еĵ�����ʧЧ������hash��洢�����ݾ�ʧЧ�ˡ�
                //����ʹ�õ���splice���������м��ĳ������ƶ�����λ�á�
                int oldkey = valueList_.back().first;
                LIST::iterator oldone = valueList_.end();
                --oldone;
                valueList_.splice(valueList_.begin(), valueList_, oldone);
                keyIndex_.erase(oldkey);

                // �ٲ�����Ԫ�ص��б�ͷ
                valueList_.begin()->first = key;
                valueList_.begin()->second = value;
                keyIndex_[key] = valueList_.begin();
            }
        }

        return true;
    }

    bool remove(const Key& key)
    {
        zl::thread::LockGuard<LockType> lock(mutex_);
        return removeWithHolder(key);
    }

    bool hasKey(const Key& key) const
    {
        zl::thread::LockGuard<LockType> lock(mutex_);
        return keyIndex_.find(key) != keyIndex_.end();
    }

    size_t size() const
    {
        zl::thread::LockGuard<LockType> lock(mutex_);
        return valueList_.size();
    }

    size_t capacity() const
    {
        return capacity_;
    }

    bool isEmpty() const
    {
        zl::thread::LockGuard<LockType> lock(mutex_);
        return valueList_.empty();
    }

    bool isFull() const
    {
        zl::thread::LockGuard<LockType> lock(mutex_);
        return keyIndex_.size() == capacity_;
    }

private:
    void clear()
    {
        zl::thread::LockGuard<LockType> lock(mutex_);
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
    size_t                 size_;
    mutable LockType       mutex_;
};

#endif /* ZL_LRUCACHE_H */