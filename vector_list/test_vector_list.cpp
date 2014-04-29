#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <list>
#include <array>
#include "HighPrecisionTime.h"

template < typename T>
std::string ToStr(const T& t)
{
	std::ostringstream oss;
	oss.str("");
	oss << t;
	return oss.str();
}

const int MAX_SIZE = 100000;

//ֻ��ָ��ʱ������vector�������
std::list<int> list1;
std::vector<int> vec1;
std::array<int, MAX_SIZE> myArr1;
void test_insert_int()
{


	for (int i = 0 ; i< MAX_SIZE; i++)
	{
		myArr1[i] = i+1;
	}

	HighPrecisionTime watch;

	watch.Reset();
	for (int i = 0 ; i< MAX_SIZE; i++)
	{
		list1.push_back(myArr1[i]);
	}
	std::cout<<"insert " << MAX_SIZE << " ints to list,   cost "<<watch.ElapsedTimeInMill()<<" ms\n";

	watch.Reset();
	for (int i = 0 ; i< MAX_SIZE; i++)
	{
		vec1.push_back(myArr1[i]);
	}
	std::cout<<"insert " << MAX_SIZE << " ints to vector, cost "<<watch.ElapsedTimeInMill()<<" ms\n";
}

//����string�ȿ������۱Ƚϴ�ʱ������list������죬��Ϊ��ʱvector�Ŀ����ƶ����۸���
std::list<std::string> list2;
std::vector<std::string> vec2;
std::array<std::string, MAX_SIZE> myArr2;
void test_insert_string()
{
	for (int i = 0 ; i< MAX_SIZE; i++)
	{
		myArr2[i] = ToStr(i+1);
	}

	HighPrecisionTime watch;

	watch.Reset();
	for (int i = 0 ; i< MAX_SIZE; i++)
	{
		list2.push_back(myArr2[i]);
	}
	std::cout<<"insert " << MAX_SIZE << " strings to list,   cost "<<watch.ElapsedTimeInMill()<<" ms\n";

	watch.Reset();
	for (int i = 0 ; i< MAX_SIZE; i++)
	{
		vec2.push_back(myArr2[i]);
	}
	std::cout<<"insert " << MAX_SIZE << " strings to vector, cost "<<watch.ElapsedTimeInMill()<<" ms\n";
}

/****************************************************************
* �˺������� http://www.cnblogs.com/clayman/p/3654768.html
* ��֤����ʹ����Ƶ�����������vectorҲ����list�ԭ��
*   1. list��Ҫռ�ø����ڴ棬���vector���Ǳ�֤Ԫ��λ���������ڴ棬��������Ҫ�ģ�
*   2. Cache missing���µ�������ʧ�����ȸ���Ԫ�ػ����ء�
*   3. ���ִ�CPU��˵�������ٶ��Ѿ��ǳ��죬һ��cache missing�ͻ��˷�n��cpu���ڣ�������֯���ݣ���cpu���ٵȴ�ʱ�����ִ�cpu�ǳ���Ҫ���Ż��ֶΡ�
* ע�⣬�������ʾ����ֻ��Ϊ��չʾcache missing����Ҫ�ԣ���������������������ŷ���������ʵ������¶��ڸ���������˵�����Ÿ��ƴ��۵���ߣ�vectorδ�ؾ�����ʤ����:)��
****************************************************************/
std::array<int, MAX_SIZE> myArr;
std::list<int> myList;
std::vector<int> myVec;
void test_insert_int_keep_order()
{
	for(int i = 0; i < MAX_SIZE; i++)
		myArr[i] = rand() % 2000;

	//Ԥ�ȷ���ռ�
	myVec.reserve(MAX_SIZE);
	myList.resize(MAX_SIZE,10000);

	std::cout << std::setprecision(10);

	HighPrecisionTime watch;

	watch.Reset();	
	for(int i = 0; i < MAX_SIZE; i++)  //����������뵽list�У��ұ�������״̬
	{
		int value = myArr[i];
		auto it = myList.begin();
		for( ; it != myList.end(); it++)
		{
			if(*it > value)
			{
				it = myList.insert(it, value);
				break;
			}
		}
		if(it == myList.end())
			myList.push_back(value);
	}
	std::cout<<"insert " << MAX_SIZE << " ints to list, and keep order,   cost "<<watch.ElapsedTimeInMill()<<" ms\n";

	watch.Reset();
	for(int i = 0; i < MAX_SIZE; i++)  //����������뵽vector�У��ұ�������״̬
	{
		int value = myArr[i];
		auto it = myVec.begin();
		for( ; it != myVec.end(); it++)
		{
			if(*it > value)
			{
				it = myVec.insert(it, value);
				break;
			}
		}
		if(it == myVec.end())
			myVec.push_back(value);
	}
	std::cout<<"insert " << MAX_SIZE << " ints to vector, and keep order, cost "<<watch.ElapsedTimeInMill()<<" ms\n";
}


int main()
{
	std::cout<<"--------------------------------------------\n";
	test_insert_int();

	std::cout<<"--------------------------------------------\n";
	test_insert_string();

	std::cout<<"--------------------------------------------\n";
	//test_insert_int_keep_order();

	system("pause");
	return 0;
}

/*************************************************
Output(Debug)
��һ�Σ�
--------------------------------------------
insert 10000 ints to list,   cost 29.1224 ms
insert 10000 ints to vector, cost 4.66314 ms
--------------------------------------------
insert 10000 strings to list,   cost 44.7178 ms
insert 10000 strings to vector, cost 695.75 ms
--------------------------------------------
�ڶ��Σ�
--------------------------------------------
insert 100000 ints to list,   cost 241.752 ms
insert 100000 ints to vector, cost 37.4099 ms
--------------------------------------------
insert 100000 strings to list,   cost 422.486 ms
insert 100000 strings to vector, cost 16859.6 ms
--------------------------------------------

Output(Release)
��һ�Σ�
--------------------------------------------
insert 10000 ints to list,   cost 10.5768 ms
insert 10000 ints to vector, cost 0.209614 ms
--------------------------------------------
insert 10000 strings to list,   cost 20.4362 ms
insert 10000 strings to vector, cost 1.39453 ms
--------------------------------------------
�ڶ��Σ�
--------------------------------------------
insert 100000 ints to list,   cost 84.6288 ms
insert 100000 ints to vector, cost 1.98792 ms
--------------------------------------------
insert 100000 strings to list,   cost 66.9376 ms
insert 100000 strings to vector, cost 10.6645 ms
--------------------------------------------
*************************************************/