#include "Subject.h" 
#include "Observer.h" 

#include <iostream> 
using namespace std; 
int main(int argc,char* argv[]) 
{ 
	ConcreteSubject* sub = new ConcreteSubject(); 
	Observer* o1 = new ConcreteObserverA(sub); //ConcreteObserverAһ����ʼ����ConcreteSubject
	Observer* o2 = new ConcreteObserverB(sub); //ConcreteObserverBһ����ʼ����ConcreteSubject
	sub->SetState("old"); //ConcreteSubject(���⣬Ŀ��)�����仯���ı�����
	sub->Notify(); // �·�֪ͨ�������еĹ۲��߷�����Ӧ�仯
	sub->SetState("new"); //Ҳ������ Observer���� ,//ConcreteSubject(���⣬Ŀ��)�����仯���ı�����
	sub->Notify();  // �·�֪ͨ�������еĹ۲��߷�����Ӧ�仯

	system("pause");
	return 0; 
} 