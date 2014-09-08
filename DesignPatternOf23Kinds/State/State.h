/************************************************************************/
/* State ģʽ��Ҫ��Ҫ��Ӧ�������״̬�ı�ʱ�Ĳ�ͬ������Ե�ʵ��.
   Stateģʽ�ܺõ�ʵ���˶����״̬�߼��Ͷ���ʵ�ֵķ��룬״̬�߼��ֲ��� State ������
   ����ʵ�֣�������ʵ������Է��� Context ����ʵ�֣���Ҳ��Ϊʲô State ��������Ҫӵ
��һ��ָ�� Context ��ָ�룩 ����ʹ�����ߵı仯�໥�������ı� State ��״̬�߼����Ժ�
���׸��� Context �Ķ����� Ҳ�����ڲ�Ӱ�� State �������ǰ���´��� Context����������
�Ļ��滻����ʵ�֡� 
   Stateģʽ������Ҫ���߼���ɢ����״̬�߼��ֲ����˺ܶ�� State �������У����ѿ�����
����״̬�߼�ͼ����Ҳ�����˴����ά�����⡣ 
   State ģʽ��ʵ���У��������ؼ��㣺 
   1���� State����Ϊ Context ����Ԫ�ࣨfriend class�� ������������ State ģʽ����
Context�� protected�ӿ� ChangeSate���� �� 
   2��State ���������еĲ������� Context*������Ϊ����������ҪĿ���� State �����ͨ
�����ָ����� Context�еķ��� ���ڱ�ʾ��������û�����֣� �� ��Ҳ�� State ģʽ�� 
Strategyģʽ������������ڡ�                */
/************************************************************************/
//state.h 
#ifndef _STATE_H_ 
#define _STATE_H_ 
class Context; //ǰ������ 


class State 
{ 
public: 
	State(); 
	virtual ~State(); 
	virtual void OperationInterface(Context* ) = 0; 
	virtual void OperationChangeState(Context*) = 0; 
protected: 
	bool ChangeState(Context* con,State* st); 
private: 
	//bool ChangeState(Context* con,State* st); 
}; 


class ConcreteStateA:public State 
{ 
public: 
	ConcreteStateA(); 
	virtual ~ConcreteStateA(); 
	virtual void OperationInterface(Context* ); 
	virtual void OperationChangeState(Context*); 
protected: 
private: 
}; 


class ConcreteStateB:public State 
{ 
public: 
	ConcreteStateB(); 
	virtual ~ConcreteStateB(); 
	virtual void OperationInterface(Context* ); 
	virtual void OperationChangeState(Context*); 
protected: 
private: 
}; 


#endif //~_STATE_H_ 
