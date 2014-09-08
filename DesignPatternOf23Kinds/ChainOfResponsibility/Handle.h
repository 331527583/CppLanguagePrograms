/************************************************************************/
/* Chain of  Responsibility ģʽ������ʵ��������һ�����⽫���ܴ���һ������Ķ�����
�ӳ�һ����������������������ϴ��ݣ�ֱ���ж���������󣨿�����Ҫ�ṩһ��Ĭ�ϴ���
����������࣬���� MFC �е� CwinApp �ࣩ �� Chain of Responsibilityģʽ�� 
ConcreteHandler���Լ��ĺ�̶������´�����Ϣ�Ķ��󣩼�¼���Լ��ĺ�̱��У���һ����
����ʱ��ConcreteHandler ���ȼ�鿴�Լ���û��ƥ��Ĵ������ ����о��Լ����� 
���򴫵ݸ����ĺ�̡� ��Ȼ����ʾ��������Ϊ�˼򻯣�ConcreteHandler ֻ�Ǽ򵥵ļ�鿴��
����û�к�̣��еĻ������󴫵ݸ���̽��д���û�еĻ����Լ����� 

Chain of Responsibilityģʽ������һ���ŵ���Ǹ�ϵͳ����������ԣ�����ķ�������ȫ
����֪��������ᱻ�ĸ�Ӧ�����������ؽ�����ϵͳ������ԡ�                                                                      */
/************************************************************************/
//Handle.h 
#ifndef _HANDLE_H_ 
#define _HANDLE_H_ 
#include <iostream> 
using namespace std; 


class Handle 
{ 
public: 
	virtual ~Handle()
	{
		delete _succ;
	}
	virtual void HandleRequest()=0; 
	virtual int HandleMouseClick()=0;
	void SetSuccessor(Handle* succ)
	{
		this->_succ = succ;
	}
	Handle* GetSuccessor()
	{
		return _succ;
	}
protected: 
	Handle()
	{
		_succ = 0;
	}
	Handle(Handle* succ)
	{
		this->_succ = succ;
	}
private: 
	Handle* _succ; 
}; 

class ConcreteHandleA:public Handle 
{ 
public: 
	ConcreteHandleA(){	}
	~ConcreteHandleA(){	}
	ConcreteHandleA(Handle* succ):Handle(succ){	}
	void HandleRequest()
	{
		if (this->GetSuccessor() != 0) 
		{ 
			cout<<"ConcreteHandleA �ҰѴ���Ȩ����̽ڵ�....."<<endl; 
			this->GetSuccessor()->HandleRequest(); 
		} 
		else 
		{ 
			cout<<"ConcreteHandleA û�к���ˣ��ұ����Լ�����...."<<endl; 
		} 
	}

	int HandleMouseClick()
	{
		//���������飬�����ദ����¼�������1�����򷵻�0
		return 0;
	}
 
};


class ConcreteHandleB:public Handle 
{ 
public: 
	ConcreteHandleB(){	}
	~ConcreteHandleB(){	} 
	ConcreteHandleB(Handle* succ):Handle(succ){	}
	void HandleRequest()
	{
		if (this->GetSuccessor() != 0) 
		{ 
			cout<<"ConcreteHandleB �ҰѴ���Ȩ����̽ڵ�....."<<endl; 
			this->GetSuccessor()->HandleRequest(); 
		} 
		else 
		{ 
			cout<<"ConcreteHandleB û�к���ˣ��ұ����Լ�����...."<<endl; 
		} 
	}

	int HandleMouseClick()
	{
		//���������飬�����ദ����¼�������1�����򷵻�0
		cout<<"ConcreteHandleB������HandleMouseClick�����¼�\n";
		return 1;
	}
}; 
//----------------------------------------lizheng 2011-11-15 15:32:18
//����һ��Ĭ���࣬��Ĭ�ϴ�����������
class DefaultHandle :public Handle
{
public: 
	DefaultHandle(){	}
	~DefaultHandle(){	} 
	DefaultHandle(Handle* succ):Handle(succ){	}
	void HandleRequest()
	{
		cout<<"�޶�������¼�����Ĭ���ദ��\n";
	}

	int HandleMouseClick()
	{
		//���������飬�����ദ����¼�������1�����򷵻�0
		cout<<"DefaultHandle������HandleMouseClick�����¼�\n";
		return 1;
	}
};
#endif //~_HANDLE_H_ 