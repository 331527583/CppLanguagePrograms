#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

class Int
{
public:
	Int(int i=0):m_i(i){}
	void print()const
	{
		cout<<"[ "<<m_i<<" ]\n";
	}
	~Int(){}
	int m_i;
};
void print(int i)
{
	cout<<i<<"\t";
}
template<typename T>
struct myprint
{
public:
	void operator()(const T& t)
	{
		cout<<t<<"\t";
	}
};
void test1()
{
	int ai[6] = {0,1,2,3,4,5};
	vector<int> vec(ai,ai+6);

	//�˴���myprint<int>()��һ����ʱ���󣬶�����һ����������
	//������󱻴���for_each�У���for_each����ʱ����ʱ�������������Ҳ�ͽ�����
	for_each(vec.begin(),vec.end(),myprint<int>());
	cout<<endl;
}
void test2()
{
	ostream_iterator<int> outite(cout,"\t");

	int ai[6] = {2,21,12,7,19,23};
	vector<int> vec(ai,ai+6);

	//�ҳ���С�� 12 ��Ԫ�ظ���
	cout<< count_if(vec.begin(),vec.end(),not1(bind2nd(less<int>(),12))) << endl;

	//��ÿ��Ԫ��vִ�У�v+2)*3,Ȼ�������outite
//	transform(vec.begin(),vec.end(),outite,compose1(bind2nd(multiplies<int>(),3),bind2nd(plus<int>(),2) )) <<endl;

	//���½�����Ԫ��������ж��ַ���
	//1.�����outite
	copy(vec.begin(),vec.end(),outite);		cout<<endl;
	//for_each�ĵ���������������ָ���������ֻ�ܴ�һ������
	//2.�Ժ���ָ��
	for_each(vec.begin(),vec.end(),print);	cout<<endl;
	//3.�����ι���һ�㺯��
	for_each(vec.begin(),vec.end(),ptr_fun(print));	cout<<endl;
	//4.�Ժ�������
	for_each(vec.begin(),vec.end(),myprint<int>());	cout<<endl;

	Int t1(1),t2(2),t3(3),t4;
	vector<Int> vv;
	vv.push_back(t1);
	vv.push_back(t2);
	vv.push_back(t3);
	vv.push_back(t4);
	//5.�����ι��ĳ�Ա����
	for_each(vv.begin(),vv.end(),mem_fun_ref(&Int::print));
}
//template<typename T>
struct del_sequence_ptr //: public std::unary_function<T,void>
{
public:
	template<typename T>
	void operator()(T *t)
	{
		delete t;
	}
};
void test3()
{
	typedef std::vector<Int*>			IntContainer;
	//vector<Int*> vec;
	IntContainer vec;
	vec.push_back(new Int);
	vec.push_back(new Int(178));
	for_each(vec.begin(),vec.end(),del_sequence_ptr());

	vector<string*> vs;
	vs.push_back(new string("df"));
	for_each(vs.begin(),vs.end(),del_sequence_ptr());
}
int main()
{
	test1();
	test2();
	test3();
	system("pause");
	return 0;
}