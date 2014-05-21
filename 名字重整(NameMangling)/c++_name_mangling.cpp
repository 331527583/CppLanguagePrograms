#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include "osDefine.h"
#include "Demangle.h"

////Demangle.h Demangle.cpp ��Դ��glog,����ʵ��ֻ�ɽ���linuxϵͳgcc������������������

#ifdef OS_WINDOWS
#include <Windows.h>
#include <DbgHelp.h>				/*����ʵ�ֽ�����������ֽ���Ϊԭʼ����*/
#pragma comment(lib,"DbgHelp.lib")
#elif defined(OS_LINUX)
#include<cxxabi.h>					/*����ʵ�ֽ�����������ֽ���Ϊԭʼ����*/
#else
#error "You must be include osDefine.h firstly"
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

#define IMPLEMENT_ALL   /**�򿪸ú꣬�������Ϻ���ʵ��*/
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
void UnDecorateName(const char *szDecorateName)
{
	const size_t max_size = 1024;
	//char szDecorateName[max_size] = {0};
	char szUnDecorateName[max_size] = {0};
	//printf("Please Input Mangled Name: ");
	//scanf("%s", szDecorateName);

#ifdef OS_WINDOWS
	if (::UnDecorateSymbolName(szDecorateName, szUnDecorateName, sizeof(szUnDecorateName), UNDNAME_COMPLETE) == 0)
	{
		printf("UnDecorateSymbolName Failed. GetLastError() = %d", GetLastError());
	}
	else
	{
		printf("Name after  Mangled : %s \nName before Mangled : %s\n", szDecorateName, szUnDecorateName);
	}
#else
	int status;
	size_t n = max_size;
	abi::__cxa_demangle(szDecorateName,szUnDecorateName,&n,&status);
	printf("Name after  Mangled : %s \nName before Mangled : %s\n", szDecorateName, szUnDecorateName);
#endif
}

class H
{
public : 
	H();

};
int main(void)
{
	int i = 1;
	float f = 1.0;
	std::vector<std::string> vec;
	NP1::C *pac = new NP1::C;
	NP2::C *pbc = new NP2::C;

#if 1
	func(f);
	func(i);

	NP1::func(i);
	pac->func(i);

	NP2::func(i);
	pbc->func(i);

	func(vec);
#endif
	UnDecorateName("?func@@YAHABV?$vector@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@2@@std@@@Z");
	std::cout << "---------------------------------\n";
	UnDecorateName("?func@NP1@@YAHH@Z");
	std::cout << "---------------------------------\n";
	UnDecorateName("??0H@@QAE@XZ");
	std::cout << "---------------------------------\n";

	//����������linux��gcc����������������֣���Windows�½������ɹ�
	UnDecorateName("_ZTCN10LogMessage9LogStreamE0_So");
	UnDecorateName("_ZN3FooD1Ev");
	UnDecorateName("_ZNSoD0Ev");
	
	//H h;
	char buf[4096];
	Demangle("_ZTCN10LogMessage9LogStreamE0_So",buf,4096);
	std::cout << buf <<"\n---------------------------------\n";

	memset(buf,'0',4096);
	Demangle("_ZN3FooD1Ev",buf,4096);
	std::cout << buf <<"\n---------------------------------\n";

	memset(buf,'0',4096);
	Demangle("??0H@@QAE@XZ",buf,4096);		//Windows,VS 2010���������֣�glog��DemangleҲ�ǽ������ɹ�
	std::cout << buf <<"\n---------------------------------\n";

	//system("pause");
	return 0;
}