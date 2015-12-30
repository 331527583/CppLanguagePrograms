//Singleton.h
#ifndef _SINGLETON_H_
#define _SINGLETON_H_
#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton *Instance()
    {
        if (_instance == 0)
        {
            _instance = new Singleton();
        }
        return _instance;
    }
protected:
    Singleton()
    {
        cout << "Singleton...." << endl;
    }
private:
    static Singleton *_instance;
};
#endif //~_SINGLETON_H_ 

//Singleton* Singleton::_instance = new Singleton; //ȫ�ֳ�ʼ�������Բ������ж��Ƿ��ʼ��
Singleton *Singleton::_instance = 0;

//------------------------------ģ����ʽ---------------------------
template<typename T>
class TSingleTon
{
public :
    static T *getSingleTonPtr()
    {
        return instance;
    }
    static T &getSingleTonRef()
    {
        return *instance;
    }
private:
    static T *instance;
};

template < typename T >
T *TSingleTon<T>::instance = new T;//0;

class Test
{
public:
    int i ;
    void print()
    {
        cout << "Test->i= " << i << endl;
    }
};

#define Test_Ton TSingleTon<Test>
//------------------------------ģ����ʽ +  �̳���ʽ---------------------------
class FGHYU : public TSingleTon<FGHYU>
{
public:
    int i ;
    void print()
    {
        cout << "FGHYU->i= " << i << endl;
    }
};