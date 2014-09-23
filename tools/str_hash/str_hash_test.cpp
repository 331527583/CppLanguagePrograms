#include <iostream>
#include "base/StringHash.h"
using namespace std;

void test_strhash(const char *str)
{
	cout<< SDBMHash(str) <<"\n";
	cout<< RSHash(str) <<"\n";
	cout<< JSHash(str) <<"\n";
	cout<< BKDRHash(str) <<"\n";
	cout<< DJBHash(str) <<"\n";
	cout<< FNVHash(str)<<"\n";
}

int main()
{
	const char *teststr = "Hello, Lizheng!";
	test_strhash(teststr);
	cout<<"----------------------\n";

	test_strhash("�й�������");

	system("pause");
	return 0;
}