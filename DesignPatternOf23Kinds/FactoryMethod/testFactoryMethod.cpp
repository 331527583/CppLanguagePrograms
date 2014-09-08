#include "Factory.h" 
#include "Product.h" 
#include <iostream> 
using namespace std; 


int main(int argc,char* argv[]) 
{ 
	Factory* fac = new ConcreteFactory(); 
	Product* p = fac->CreateProduct(); 

	//��ConcreteProduct�������һ���ǽӿ��еķ�����Product��ָ��϶�����ֱ�ӷ��ʡ�
	//���ǿ���ʹ����������ת���ɾ�������ConcreteProduct��ָ�룬���Ϳ��Է���ConcreteProduct�����г�Ա��
	// ����������ת�����������ܹ��ɹ���Ҳ������ȫ����û��ǽ��ӿ���ȡ��������Product��.lizheng 20111110 �������
	ConcreteProduct* cp = dynamic_cast<ConcreteProduct*>(p);
	cp->test();
	system("pause");
	return 0; 
} 