/************************************************************************/
/*  Command ģʽͨ���������װ��һ������Command���У���������Ľ����ߴ�ŵ�
����� ConcreteCommand ���У�Receiver���У��Ӷ�ʵ�ֵ��ò����Ķ���Ͳ����ľ���
ʵ����֮��Ľ�� Command ģʽ�ṹͼ�У�������Ľ����ߣ������ߣ��ŵ� Command
�ľ�������ConcreteCommand �У���������ʱ��Invoker ���� Invoke ��Ϣ���� 
Command ����,ConcreteCommand ���������󽻸� Receiver������д���
	Command ģʽ��ʵ�ֵ�ʵ�ֺ�˼�붼�ܼ򵥣���ؼ����ǽ�һ�������װ��һ������
��Command�� �����ṩ�������Receiver�� �����Command ������ Invoker���
	֧��ȡ��������Command��Excute��������ʵʩ����ǰ��״̬�洢��������ȡ������ʱ
���״̬���������ò�����Ӱ�졣Command�ӿڱ������һ��UnExcute�������ò���ȡ����
һ��Excute���õ�Ч����ִ�е�����洢��һ����ʷ�б��С���ͨ��������ǰ������
һ�б��ֱ����UnExcute��Excute��ʵ���������޵ġ�ȡ�����͡������� ��*/
/************************************************************************/
//Command.h 
#ifndef _COMMAND_H_ 
#define _COMMAND_H_ 
#include <iostream>
#include <list>
#include <vector>
#include "Reciever.h"
class Reciever; 

class Command 
{ 
public: 
	virtual ~Command(){	}
	virtual void Execute() = 0; 
protected: 
	Command(){	}
private: 
}; 


class ConcreteCommandA : public Command 
{ 
public: 
	ConcreteCommandA(RecieverA* rev)
	{
		this->_rev = rev;
	}
	~ConcreteCommandA()
	{
		delete _rev;
	} 
	void Execute()
	{
		this->_rev->Action(); 
		std::cout<<"ConcreteCommandA..."<<std::endl; 
	}
protected: 
private: 
	RecieverA* _rev; 
}; 
class ConcreteCommandB : public Command 
{ 
public: 
	ConcreteCommandB(RecieverB* rev)
	{
		this->_rev = rev;
	}
	~ConcreteCommandB()
	{
		delete _rev;
	} 
	void Execute()
	{
		this->_rev->Action(); 
		std::cout<<"ConcreteCommandB..."<<std::endl; 
	}
protected: 
private: 
	RecieverB* _rev; 
}; 
//----------------------------------------------------------------------------------------------
/************************************************************************/
/* ���ǿ��Խ���������ߵĴ�����������Ϊ�������� Command ����ʵ��Ҳ����
�ص��Ļ��ƣ�Callback����ʵ����һ�㣬Ҳ����˵���������������ַ���ڶ����ڲ���
ͨ���������ݸ�Command ����Command �������ʵ���ʱ��Invoke �����ʱ��
�ٵ��øú������������Ҫ�õ� C++�е����Ա����ָ��ĸ���           
���ڼ򵥵Ĳ���ȡ���Ͳ������������ , ������һ����ģ����������������Ľ����ߡ���
�ǽ�Ϊ��Щ�����һ��ģ������ SimpleCommand. ��SimpleReciever���Ͳ�����SimpleCommand��
��ά��һ�������߶����һ������֮��İ� ,����һ��������ָ��һ����Ա������ָ��洢
�ġ�
	��һ�����������ڼ���������ӵ������Ҫά�����ǵĽ����ߣ����һ�Ҫ��
�ǲ�������ʱ��Ҫ��������ȡ��������״̬��*/
/************************************************************************/
template <class Reciever> 
class SimpleCommand : public Command 
{ 
public: 
	typedef void (Reciever::* Action)(); 
	SimpleCommand(Reciever* rev,Action act) //�������洢�����ߺͶ�Ӧʵ�������еĶ�����Excute����ʵʩ�����ߵ����������
	{ 
		_rev = rev; 
		_act = act; 
	} 
	virtual void Execute() 
	{ 
		(_rev->* _act)(); 
	} 
	~SimpleCommand() 
	{ 
		delete _rev; 
	} 
protected: 
private: 
	Reciever* _rev; 
	Action _act; 
}; 

//----------------------------------------------------------------------------------------------
/************************************************************************/
/*MacroCommand����һ�����������У����ṩ�����Ӻ�ɾ��������Ĳ��������ﲻ��Ҫ��ʽ��
�����ߣ���Ϊ��Щ�������Ѿ����������Ǹ��ԵĽ����ߡ�MacroCommand�Ĺؼ�������Exectue��
Ա���������������е��������������Ե�Exectue������
ע�⣬���MacroCommandʵ��ȡ������, ��ô��������������������Exectue��ʵ���෴��˳
��ִ�и��������ȡ�����������, MacroCommand�����ṩ��������������Ĳ�����
MacroCommandҲ����ɾ�����������*/
/************************************************************************/

class MacroCommand : public Command 
{
public:	
	MacroCommand(){	}
	virtual ~MacroCommand(){	}

	virtual void Add(Command* com)
	{
		this->_cmds.push_front(com);
	}
	virtual void Remove(Command* com)
	{
		_cmds.remove(com);
	}
	virtual void Execute()
	{
		for(std::list<Command*> ::iterator p  = _cmds.begin();p!=_cmds.end();p++)
		{
			Command* c = *p;
			c->Execute();
		}
	}
private:
	std::list< Command* >  _cmds;
};



#endif //~_COMMAND_H_ 
