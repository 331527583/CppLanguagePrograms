#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <array>
#include "HighPrecisionTime.h"


const int MAX_SIZE = 500000;

std::array<int, MAX_SIZE> myArr;
std::list<int> myList;
std::vector<int> myVec;

/****************************************************************
* �˴������� http://www.cnblogs.com/clayman/p/3654768.html
* ��֤����ʹ����Ƶ�����������vectorҲ����list�ԭ��
*   1. list��Ҫռ�ø����ڴ棬���vector���Ǳ�֤Ԫ��λ���������ڴ棬��������Ҫ�ģ�
*   2. Cache missing���µ�������ʧ�����ȸ���Ԫ�ػ����ء�
*   3. ���ִ�CPU��˵�������ٶ��Ѿ��ǳ��죬һ��cache missing�ͻ��˷�n��cpu���ڣ�������֯���ݣ���cpu���ٵȴ�ʱ�����ִ�cpu�ǳ���Ҫ���Ż��ֶΡ�
* ע�⣬�������ʾ����ֻ��Ϊ��չʾcache missing����Ҫ�ԣ���������������������ŷ���������ʵ������¶��ڸ���������˵�����Ÿ��ƴ��۵���ߣ�vectorδ�ؾ�����ʤ����:)��
****************************************************************/
void test()
{
	//����MAX_SIZE�������
	for(int i = 0; i < MAX_SIZE; i++)
		myArr[i] = rand() % 2000;

	//Ԥ�ȷ���ռ�
	myVec.reserve(MAX_SIZE);
	myList.resize(MAX_SIZE,10000);

	std::cout << std::setprecision(10);

	HighPrecisionTime watch;
	watch.Reset();

	//����������뵽vector�У��ұ�������״̬
	for(int i = 0; i < MAX_SIZE; i++)
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
	std::cout << watch.ElapsedTimeInMill()<<"����\n";
	
	watch.Reset();
	//����������뵽list�У��ұ�������״̬
	for(int i = 0; i < MAX_SIZE; i++)
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
	std::cout << watch.ElapsedTimeInMill()<<"����\n";
}

int main()
{
	test();
	system("pause");
	return 0;
};