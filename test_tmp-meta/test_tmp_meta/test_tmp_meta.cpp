#include <iostream>
#include <vector>
#include "meta/meta_util.hpp"
using namespace std;

void test_type_pod()
{
	class s1
	{ };
	class s2
	{
	public:
		virtual ~s2(){ }
	};

	must_be_pod<int>      m1; // Ok, int   �� pod
	must_be_pod<void*>    m2; // Ok, void* �� pod
	must_be_pod<s1>       m3; // Ok, s1    �� pod
	//	must_be_pod<s2>       m4; // Error, s2  ���� pod��s2 ���麯����
	must_be_pod<void>     m5; // Ok, void ����pod�������ػ���
}

void test_have_inherit()
{
	class Base
	{

	};
	class Derived : public Base
	{

	};
	class BaseImpl : private Base
	{

	};

	must_have_inherit<Derived, Base>     m1;  // Ok, Derived �� Base ������
	//	must_have_inherit<Base, Derived>     m2;  // Error
	must_have_inherit<Derived, Derived>  m3;  // Ok
	must_have_inherit<Base, Base>        m4;  // Ok
	//	must_have_inherit<BaseImpl, Base>    m5;  // Error
}

void test_be_subscriptable()
{
	struct subs
	{
	public:
		int operator [](size_t index) const{ return 1; }
	};

	struct not_subs
	{	};

	{
		//must_be_subscriptable<int[]>    a; // OK, int*���԰��±귽ʽ����
		must_be_subscriptable<int*>     b; // OK, int*���԰��±귽ʽ����
		must_be_subscriptable<subs>     c; // OK, subs���԰��±귽ʽ����
		//	must_be_subscriptable<not_subs> d; // Error, not_subs�����԰��±귽ʽ���ʣ��������
		must_be_subscriptable<std::vector<int>> e; // OK, std::vector Ҳ���԰��±귽ʽ����
	}
	{
		//must_be_subscriptable_as_decayable_pointer<int[]>    a; // OK, int*���԰��±귽ʽ����
		must_be_subscriptable_as_decayable_pointer<int*>     b; // OK, int*���԰��±귽ʽ����
		//	must_be_subscriptable_as_decayable_pointer<subs>     c; // Error, subs������[]�ģ�������ԭ��ָ��
		//	must_be_subscriptable_as_decayable_pointer<not_subs> d; // not_subs�����԰��±귽ʽ���ʣ��������
		//	must_be_subscriptable_as_decayable_pointer<std::vector<int>> e; // Error, vector������[]�ģ�������ԭ��ָ��
	}
}

void test_have_same_size()
{
	must_be_same_size<int, int>   a; // Ok
	must_be_same_size<int, long>  b; // Ok or Error��������Ӳ���ܹ����������
	must_be_same_size<int, void>  c; // Ok , ģ��ƫ�ػ�����ͬ
	must_be_same_size<void, int>  d; // Ok
	must_be_same_size<void, void> e; // Ok
}

int main()
{
	test_type_pod();
	test_have_inherit();
	test_be_subscriptable();
	test_have_same_size();

	system("pause");
	return 0;
}