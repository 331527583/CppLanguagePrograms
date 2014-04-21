#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

#if defined(_WIN32) || defined(WIN32)        /**Windows*/
#define WINDOWS_IMPL
#include <Windows.h>
#include <DbgHelp.h>				/*����ʵ�ֽ�����������ֽ���Ϊԭʼ����*/
#pragma comment(lib,"DbgHelp.lib")
#else
#define LINUX_IMPL
#include<cxxabi.h>					/*����ʵ�ֽ�����������ֽ���Ϊԭʼ����*/
#endif


int /*__cdecl*/ func(int);//windowsƽ̨���ں�����ǰ�ɼ�__cdecl��__stdcall��__fastcall��Ĭ��__cdecl

float  func(float); 

int    func(const std::vector<std::string>& vec);

namespace NP1
{
	int func(int);

	class C 
	{
	public:
		int func(int);
	};
};

namespace NP2
{
	int func(int);

	class C
	{
	public:
		int func(int);
	};
};

//#define IMPLEMENT_ALL   /**�򿪸ú꣬�������Ϻ���ʵ��*/
#ifdef IMPLEMENT_ALL

int func(int) { return 1; }

float func(float) { return (float)1.11; }

int func(const std::vector<std::string>& vec) { return 0; }

namespace NP1
{
	int func(int) { return 2; }

	int C::func(int) { return 3; }
};

namespace NP2
{
	int func(int) { return 4; }

	int C::func(int) { return 5; }
};

#endif

/******************************************************
��������������ֽ�����ԭ����ԭ�����֣�Windows/Linux��
*******************************************************/
void UnDecorateName()
{
	const size_t max_size = 1024;
	char szDecorateName[max_size] = {0};
	char szUnDecorateName[max_size] = {0};
	printf("Please Input Mangled Name: ");
	scanf("%s", szDecorateName);

#ifdef WINDOWS_IMPL
	if (::UnDecorateSymbolName(szDecorateName, szUnDecorateName, sizeof(szUnDecorateName), UNDNAME_COMPLETE) == 0)
	{
		printf("UnDecorateSymbolName Failed. GetLastError() = %d", GetLastError());
	}
	else
	{
		printf("Name after  Mangled : %s \nName before Mangled : %s\n", szDecorateName, szUnDecorateName);
	}
	system("pause");
#else
	int status;
	size_t n = max_size;
	abi::__cxa_demangle(szDecorateName,szUnDecorateName,&n,&status); 
	printf("Name after  Mangled : %s \nName before Mangled : %s\n", szDecorateName, szUnDecorateName);
#endif
}


int main(void)
{
	int i = 1;
	float f = 1.0;
	std::vector<std::string> vec;
	NP1::C *pac = new NP1::C;
	NP2::C *pbc = new NP2::C;

#if 0
	func(f);
	func(i);

	NP1::func(i);
	pac->func(i);

	NP2::func(i);
	pbc->func(i);

	func(vec);
#endif

	UnDecorateName();
	//system("pause");
	return 0;
}