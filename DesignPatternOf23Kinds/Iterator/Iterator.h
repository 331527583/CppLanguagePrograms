/************************************************************************/
/* Iterator ģʽҲ�������������һ���ۺ϶���ı������⣬���Ծۺϵı�����װ��һ��
���н��У������ͱ����˱�¶����ۺ϶�����ڲ���ʾ�Ŀ��ܡ�  Iteratorģʽ��ʵ�ִ���
�ܼ򵥣�ʵ����Ϊ�˸��õر��� Aggregate ��״̬�����ǿ��Ծ�����СAggregate��public
�ӿڣ� ��ͨ����Iterator��������λAggregate����Ԫ������IteratorһЩ��Ȩ����÷���
Aggregate ˽�����ݺͷ����Ļ��ᡣ */
/************************************************************************/
//Iterator.h
#ifndef _ITERATOR_H_
#define _ITERATOR_H_
class Aggregate;
typedef int Object;


class Iterator
{
public:
    virtual ~Iterator();
    virtual void First() = 0;
    virtual void Next() = 0;
    virtual bool IsDone()  = 0;
    virtual Object CurrentItem() = 0;
protected:
    Iterator();
private:
};

class ConcreteIterator: public Iterator
{
public:
    ConcreteIterator(Aggregate *ag , int idx = 0);
    ~ConcreteIterator();
    void First();
    void Next();
    bool IsDone();
    Object CurrentItem();
protected:
private:
    Aggregate *_ag;
    int _idx;
};
#endif //~_ITERATOR_H_ 
