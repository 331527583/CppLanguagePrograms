/************************************************************************/
/* ��ģʽ�� Adapter ���ü̳еķ�ʽ���� Adaptee�Ľӿڣ�
   ����ģʽ�� Adapter�в�����ϵķ�ʽʵ�� Adaptee�ĸ��� */
/************************************************************************/

#ifndef _ADAPTEROfObject _H_
#define _ADAPTEROfObject _H_
#include <iostream>


class TargetOfObject
{
public:
    TargetOfObject() {	}
    virtual ~TargetOfObject () {	}
    virtual void Request()
    {
        std::cout << "TargetOfObject::Request" << std::endl;
    }
};

class AdapteeOfObject
{
public:
    AdapteeOfObject () {	}
    ~AdapteeOfObject () {	}
    void SpecificRequest()
    {
        std::cout << "AdapteeOfObject::SpecificRequest" << std::endl;
    }
};

class AdapterOfObject : public TargetOfObject
{
public:
    AdapterOfObject (AdapteeOfObject *ade)
    {
        this->_ade = ade;
    }
    ~AdapterOfObject ()
    {
        delete _ade;
    }
    void Request()
    {
        _ade->SpecificRequest();
    }
private:
    AdapteeOfObject *_ade;
};

#endif //~_ADAPTEROfObject _H_ 

