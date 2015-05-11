#pragma  once

// Ŀǰֻ��ʵ���Զ������͵�����ʽʵ�֣��Է����û������ͣ�int�ȣ����޷�����
template <class ListableClass>
class Listable
{
public:
    Listable() : next_(NULL), prev_(NULL)
    {
    }

    /** �õ���һ����������� */
    ListableClass* next() const { return next_; }

    /** �õ�ǰһ����������� */
    ListableClass* prev() const { return prev_; }

    /** ������һ����������� */
    void setNext(ListableClass *next) { next_ = next; }

    /** ����ǰһ����������� */
    void setPrev(ListableClass *prev) { prev_ = prev; }

private:
    ListableClass* next_;
    ListableClass* prev_;
};

template<>
class Listable < int >   // not ok
{
public:
    Listable(int *curr = 0) : next_(NULL), prev_(NULL)
    {
    }

    /** �õ���һ����������� */
    Listable < int > * next() const { return next_; }

    /** �õ�ǰһ����������� */
    Listable < int > * prev() const { return prev_; }

    /** ������һ����������� */
    void setNext(Listable < int >  *next) { next_ = next; }

    /** ����ǰһ����������� */
    void setPrev(Listable < int >  *prev) { prev_ = prev; }

private:
    Listable < int >   *next_;
    Listable < int >   *prev_;
};

template <class ListableClass>
class ListQueue
{
public:
    ListQueue()
        : size_(0)
        , head_(NULL)
        , tail_(NULL)
    {
        head_ = new ListableClass;
        tail_ = head_;
    }

    ~ListQueue()
    {
        delete head_;
        tail_ = NULL;
    }

    /** �õ�������Ԫ�ظ��� */
    int size() const
    {
        return size_;
    }

    /** �ж϶����Ƿ�Ϊ�� */
    bool empty() const
    {
        return 0 == size_;
    }

    /** �õ�ָ����׶����ָ�� */
    ListableClass* front() const
    {
        return (ListableClass*)head_->next();
    }

    /** �ڶ�β���һ����������� */
    void push(ListableClass* listable)
    {
        assert(listable != NULL);
        if (NULL == listable) return;

        ListableClass* next = listable->next();
        ListableClass* prev = listable->prev();
        if (prev != NULL) return; // �Ѿ��ڶ�����
        assert(NULL == next);

        listable->setNext(NULL);
        listable->setPrev(tail_);
        tail_->setNext(listable);
        tail_ = listable;
        ++size_;
    }

	/**
	* ��һ�����������Ӷ�����ɾ��
	* ɾ�������Ǹ�Ч�ģ���Ϊ0���ң�ֻ��Ҫ������ӹ�ϵ����
	*/
    void remove(ListableClass* listable)
    {
        assert(listable != NULL);
        if (NULL == listable) return;

        ListableClass* next = listable->next();
        ListableClass* prev = listable->prev();
        if (NULL == prev)
        {
            assert(NULL == next);
            return; // �Ѿ����ڶ�����
        }

        prev->setNext(next);
        if (NULL == next)
        {
            // β����next�Ż�ΪNULL
            tail_ = prev;
        }
        else
        {
            next->setPrev(prev);
        }

        assert(size_ > 0);
        listable->setPrev(NULL);
        listable->setNext(NULL);
        --size_;
    }

private:
    int size_;
    ListableClass* head_;
    ListableClass* tail_;
};
