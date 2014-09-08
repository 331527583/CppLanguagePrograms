#include <iostream>
#include <cstdlib>
using namespace std;

size_t strlen1(const char* s)
{
	return strlen(s);
}

void test_ptr()
{
	int a = 100, b = 200;

	//-------����ָ��-------
	const int *p1 = &a;
	a = 300;     //OK,��Ȼ����ͨ��ԭ���������޸�ֵ��
	//*p1 = 56;  //Error,*p1��const int�ģ������޸ģ�������ָ�벻���޸���ָ���ַ
	p1 = &b;     //OK,ָ�뻹����ָ��𴦣���Ϊָ��ֻ�Ǹ���������������ָ��

	//-------ָ�볣��-------//
	int*  const p2 = &a;
	a = 500;	 //OK,��Ȼ����ͨ��ԭ���������޸�ֵ��
	*p2 = 400;   //OK,ָ���ǳ�����ָ��ĵ�ַ�����Ա仯,����ָ��ĵ�ַ����Ӧ�����ݿ��Ա仯
	//p2 = &b;	 //Error,��Ϊp2��const ָ�룬��˲��ܸı�p2ָ�������

	//-------ָ�����ĳ���ָ��-------//
	const int* const p3 = &a;
	//*p3 = 1;	//Error
	//p3 = &b;	//Error
	a = 5000;	//OK,��Ȼ����ͨ��ԭ���������޸�ֵ

	//-------��ָ��-------//
	int *p4 = NULL;
	//printf("%d",*p4); //����Error��ʹ��ָ��ʱ�������ж��Ƿ��ָ��

	//-------Ұָ�루��������;ָ�룩-------//
	int *p5 = new int(5);
	delete p5;
	//p5 = NULL; //һ��Ҫ����һ��
	//printf("%d",*p5);  //����bug��delete��ָ���һ��Ҫ��0����Ȼָ��ָ��λ�ò��ɿأ������пɵ���ϵͳ�ҵ�

	//-------ָ����ڴ�й©-------//
	int *p6 = new int(6);
	p6 = new int(7); //p6ԭ��ָ����ǿ��ڴ���δ�ͷţ����p6��ָ���˱𴦣�ԭ��new���ڴ��޷����ʣ�Ҳ�޷�delete�ˣ����memory leak
}

void process_value(/*const*/ int& i) {
	std::cout << "LValue processed: " << i << std::endl;
}

void process_value(int&& i) {
	std::cout << "RValue processed: " << i << std::endl;
}

int main()
{
	int a = 0;
	process_value(a);
	process_value(1);
	test_ptr();
	system("pause");
	return 0;
}