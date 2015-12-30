/************************************************************************/
/* �ڿ����У����Ǿ�������Ҫ�ݹ鹹����״����Ͻṹ��Composite ģʽ���ṩ�˺ܺõ�
���������Composite ģʽ��ʵ������һ���������Ҫ�ṩ�����ӽڵ㣨Leaf���Ĺ�����ԣ�
����ʹ�õ��� STL  �е�vector�������ṩ������ʵ�ַ�ʽ�������顢����Hash ��ȡ�*/
/************************************************************************/

//Component.h
#ifndef _COMPONENT_H_
#define _COMPONENT_H_
class Component
{
public:
    Component() {	}
    virtual ~Component() {	}
public:
    virtual void Operation() = 0;
    virtual void Add(const Component & ) {	}
    virtual void Remove(const Component & ) {	}
    virtual Component *GetChild(int )
    {
        return 0;
    }
protected:
private:
};
#endif //~_COMPONENT_H_ 