/************************************************************************/
/*  Observer ģʽҪ���������Ϊ������һ��һ��Subject���ԶࣨObserver����������ϵ��
������������һ���仯��ʱ�����������һ���Ķ�Ҳ�ܹ�ͬ���ı䡣�����һ�����Ӿ��ǣ�
��ͬһ�����ݽ���ͳ�Ʒ���ʱ������ϣ���ܹ��ṩ������ʽ�ı�ʾ �������Ա�����ͳ����
ʾ�� ��״ͼͳ����ʾ�� �ٷֱ�ͳ����ʾ�ȣ� ����Щ��ʾ��������ͬһ�����ݣ����ǵ�Ȼ��Ҫ
�����ݸı��ʱ�����е�ͳ�Ƶ���ʾ���ܹ�ͬʱ�ı䡣Observer ģʽ���ǽ������һ�����⡣
Observer ��һ��ʵ��----- Model/View/Control��MVC��*/
/************************************************************************/
//Observer.h
#ifndef _OBSERVER_H_
#define _OBSERVER_H_
#include "Subject.h"
#include <string>
using namespace std;
typedef string State;

class Observer
{
public:
    virtual ~Observer();
    virtual void Update(Subject *sub) = 0;
    virtual void PrintInfo() = 0;
protected:
    Observer();
    State _st;
private:
};

class ConcreteObserverA: public Observer
{
public:
    virtual Subject *GetSubject();

    ConcreteObserverA(Subject *sub);
    virtual ~ConcreteObserverA();
    //���� Subject ��Ϊ����������������һ�� View ���ڶ���� Subject��
    void  Update(Subject *sub);
    void PrintInfo();
protected:
private:
    Subject *_sub;
};

class ConcreteObserverB: public Observer
{
public:
    virtual Subject *GetSubject();

    ConcreteObserverB(Subject *sub);
    virtual ~ConcreteObserverB();
    //���� Subject ��Ϊ����������������һ�� View ���ڶ���� Subject��
    void  Update(Subject *sub);
    void PrintInfo();
protected:
private:
    Subject *_sub;
};
#endif //~_OBSERVER_H_ 
