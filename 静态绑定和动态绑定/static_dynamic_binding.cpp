#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

#define MATH_PI (3.14259)

class Figure
{
public:
	Figure(){	}

	/*virtual*/ double Area()const
	{
		return 0.0;
	}
};

class Circle:public Figure
{
public:
	Circle(double radius)
	{
		radius_ = radius;
	}
	
	double Area()const
	{
		return MATH_PI*radius_*radius_;
	}
private:
	double radius_;
};

class Rectangle:public Figure
{
public:
	Rectangle(double length,double width)
	{
		length_ = length;
		width_ = width;
	}
	
	double Area()const
	{
		return length_*width_;
	}
private:
	double length_;
	double width_;
};

/*
�β�firgure��ִ�еĲ�����̬�󶨵�Figure���Area()������.�������ʵ�ֻ�Ǵӻ����е�Area()����.�����������ݹ���ʵ������ֱ�����Area()����.��������������ȷ. 

����������취���Ƕ�̬,�����Ƕ�̬��,�����̬����������ʱ������.����ֱ���Ϊ 
����ʱ��̬. 
��C++��ʵ�ֶ�̬��Ҫ���Ա������virtual�����. 
*/
void printArea(Figure &figure)
{
	std::cout<<"�����: "<<figure.Area()<<"\n";
}
void printArea(Figure *figure)
{
	std::cout<<"�����: "<<figure->Area()<<"\n";
}

class A
{
public:
	/*virtual*/ void func(){ std::cout << "A::func()\n"; }
};
class B : public A
{
public:
	void func(){ std::cout << "B::func()\n"; }
};
class C : public A
{
public:
	void func(){ std::cout << "C::func()\n"; }
};

class E
{
public:
	virtual void func(int i = 0)
	{ 
		std::cout << "E::func()\t"<< i <<"\n";
	}
};
class F : public E
{
public:
	virtual void func(int i = 1)
	{
		std::cout << "F::func()\t" << i <<"\n";
	}
};


int main(void)
{
	F* pf = new F();
	E* pe = pf;
	pf->func(); //F::func() 1  �������͸���ˣ�
	pe->func(); //F::func() 0  ��Ŷ������ʲô���������������ĺ�����ȴʹ���˻����в�����Ĭ��ֵ��
	

	C* pc = new C(); //pc�ľ�̬������������������C*����̬����Ҳ��C*��
	B* pb = new B(); //pb�ľ�̬���ͺͶ�̬����Ҳ����B*��
	A* pa = pc;      //pa�ľ�̬������������������A*����̬������pa��ָ��Ķ���pc������C*��
	pa = pb;         //pa�Ķ�̬���Ϳ��Ը��ģ��������Ķ�̬������B*�����侲̬������������ʱ���A*��
	C *pnull = NULL; //pnull�ľ�̬������������������C*,û�ж�̬���ͣ���Ϊ��ָ����NULL��

	pa->func();      //A::func() pa�ľ�̬������Զ����A*��������ָ������ĸ����࣬����ֱ�ӵ���A::func()��
	pc->func();      //C::func() pc�Ķ�����̬���Ͷ���C*����˵���C::func()��
	pnull->func();   //C::func() �������Ϊʲô��ָ��Ҳ���Ե��ú�����������ڱ����ھ�ȷ���ˣ���ָ��ղ���û��ϵ��

	//���ע�͵���C�е�void func()����
	pa->func();      //A::func() ����ͬ�ϣ�
	pc->func();      //A::func() pc����C���Ҳ���func�Ķ��壬��˵��������Ѱ�ң�
	pnull->func();   //A::func()��ԭ��Ҳ���͹��ˣ�

	//���ΪA�е�void func()�������virtual����
	pa->func();      //B::func() ��Ϊ����virtual�麯�����ԣ�pa�Ķ�̬����ָ��B*���������B�в��ң��ҵ���ֱ�ӵ��ã�
	pc->func();      //C::func() pc�Ķ�����̬���Ͷ���C*�����Ҳ������C�в��ң�
	pnull->func();   //��ָ���쳣����Ϊ��func��virtual��������˶�func�ĵ���ֻ�ܵȵ������ڲ���ȷ����Ȼ��ŷ���pnull�ǿ�ָ�룻
	
	
	std::cout << "------------------------------\n";

	Figure figure;
	Circle circle(2.0);
	Rectangle rect(3.0,4.0);

	std::cout<<"Figure�������: "<<figure.Area()<<"\n";
	std::cout<<"Circle�������: "<<circle.Area()<<"\n";
	std::cout<<"Rectangle�������: "<<rect.Area()<<"\n";
	std::cout << "------------------------------\n";

	printArea(figure);
	printArea(circle);
	printArea(rect);
	std::cout << "------------------------------\n";

	printArea(&figure);
	printArea(&circle);
	printArea(&rect);
	std::cout << "------------------------------\n";

	system("pause");
	return 0;
}

