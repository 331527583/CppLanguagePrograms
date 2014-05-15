#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <iterator>
#include <algorithm>
#include <assert.h>
#include "GBKtoUTF8.h"
using namespace std;

void GetText(bool isUtf8, std::vector<std::string>& vecStr)
{
	const char* filename = isUtf8 ? "utf8.txt" : "gbk.txt";
	std::ifstream ifs(filename);
	assert(!ifs.fail());

	while(!ifs.eof())
	{
		std::string str;
		ifs >> str;
		vecStr.push_back(str);
	}

	ifs.close();
}

void test_gbbk_utf_unicode()
{
	char const * p = "��";
	std::cout<<PrintStringAsBinaryString(p)<<"\n";
	std::cout<<PrintStringAsBinaryString("λ")<<"\n";

	//��bgbk���ո�ֿ���ÿ����������ʾ��һ���ַ��Ķ����Ʊ��룬ת��int���ͺ�ͨ��one_gbk_to_unicode���ã��õ����ַ���unicode���룬Ȼ��ͨ��one_unicode_to_utf8תΪutf-8

	//һ�Ķ����Ʊ�ʾ��11010010 10111011��D2BB��210-187����ͨ��one_gbk_to_unicodeת��Ϊunicode��4E00��Ȼ��ͨ��one_unicode_to_utf8תΪutf-8
	std::cout << std::hex<<one_gbk_to_unicode(196,227) <<"\n";
	std::cout << std::hex<<one_gbk_to_unicode(186,195) <<"\n";
	std::cout << std::hex<<one_gbk_to_unicode(210,187) <<"\n";
	std::cout << std::hex<<one_gbk_to_unicode(182,254) <<"\n";

	unsigned short uni = 0x4E00;
	char pgbk[32];
	unicode_to_gbk(&uni,pgbk,32);
	std::cout << pgbk << "\n";

	unsigned long one = 0x4E00; //0xD2BB;//0x4E00;
	unsigned char pOutput[6];
	memset(pOutput,0,6);
	one_unicode_to_utf8(one,pOutput,6);
	cout << pOutput << "\n";
	std::cout<<PrintStringAsBinaryString((char*)pOutput)<<"\n";
}

void test1()
{
	std::cout<<PrintStringAsBinaryString("��")<<"\n";
	std::cout<<PrintStringAsBinaryString("��")<<"\n";
	std::cout<<PrintStringAsBinaryString("���")<<"\n";
	const char *p = "你好";//"一"; //utf-8�ַ�
	unsigned short unibuf[32];
	utf8_to_unicode(p,unibuf,32);
	std::cout<<unibuf<<"--"<<PrintStringAsBinaryString((char*)unibuf)<<"\n";
	unsigned short wch = 0;
	one_utf8_to_unicode(p, wch);
	std::cout<<wch<<"--"<<PrintStringAsBinaryString((char*)&wch)<<"\n";

	unsigned short unicode = 0x4E00;
	char buf[32] = {'0'};
	unicode_to_utf8(unicode,buf);
}

struct set_key_comp : public binary_function<std::string, std::string, bool>
{
	bool operator()(const std::string& _Left, const std::string& _Right) const
	{
		//������ʵ�������������ʽ
		return _Right < _Left;
		return _Left < _Right;
	}
};

void test_set()
{
	std::string s1 = "��ޱ";
	std::string s2 = "������";
	std::string s3 = "��X";
	std::string s4 = "��Z";
	std::string s5 = "��ɯ";
	std::set<std::string> ss1;
	std::set<std::string,set_key_comp> ss2;
	std::cout<<PrintStringAsBinaryString(s1)<<"\t" << s1 <<"\n";
	std::cout<<PrintStringAsBinaryString(s2)<<"\t" << s2 <<"\n";
	std::cout<<PrintStringAsBinaryString(s3)<<"\t" << s3 <<"\n";
	std::cout<<PrintStringAsBinaryString(s4)<<"\t" << s4 <<"\n";
	std::cout<<PrintStringAsBinaryString(s5)<<"\t" << s5 <<"\n";

	ss1.insert(s1); ss1.insert(s2); ss1.insert(s3); ss1.insert(s4); ss1.insert(s5);
	ss2.insert(s1); ss2.insert(s2); ss2.insert(s3); ss2.insert(s4); ss2.insert(s5);

	for(std::set<std::string>::iterator itr = ss1.begin();itr!=ss1.end();++itr)
		std::cout << *itr << "\t";
	std::cout << "\n";
	for(std::set<std::string,set_key_comp>::iterator itr = ss2.begin();itr!=ss2.end();++itr)
		std::cout << *itr << "\t";
	std::cout << "\n";
	//std::copy(ss1.begin(),ss2.end(),std::back_inserter(std::cout));
	//std::copy(ss1.begin(), ss1.end(), std::back_inserter(ss2));
}

int main()
{
	test_set();
	system("pause");
	return 0;
	//test1();
	//std::cout<<"-----------------------------------------\n";
	//test_gbbk_utf_unicode();
	//std::cout<<"-----------------------------------------\n";

	std::cout<<"��: GBK: "<<PrintStringAsBinaryString("��")<<"\n";  //11010111 11010110 : 215 214
	std::cout<<"��: Unicode: "<< std::hex<<one_gbk_to_unicode(215,214) <<"\n"; //5b57
	unsigned short unicode = 0x5b57;
	char buf[32] = {'0'};
	unicode_to_utf8(unicode,buf);
	std::cout<<"��: Utf-8: "<< PrintStringAsBinaryString(buf) <<"\t"<< buf <<"\n"; //11100101 10101101 10010111 : E5 AD 97
	std::cout<<"-----------------------------------------\n";

	std::string ghello = "���";
	std::string gthank = "лл";
	std::cout<<ghello<<"\t"<<ConvertGBKToUtf8(ghello)<<"\t"<<IsTextUTF8(ghello.c_str(),ghello.size())<<"\t"<<IsTextUTF8(ghello)<<"\n";
	std::cout<<gthank<<"\t"<<ConvertGBKToUtf8(gthank)<<"\t"<<IsTextUTF8(gthank.c_str(),gthank.size())<<"\t"<<IsTextUTF8(gthank)<<"\n";

	std::vector<std::string> uVecStr;
	std::vector<std::string> gVecStr;
	GetText(true,uVecStr);
	GetText(false,gVecStr);

	std::cout<<"--------------utf8--->gbk----------------\n";
	for (std::vector<std::string>::iterator itr = uVecStr.begin();itr!=uVecStr.end();++itr)
	{
		std::cout<<*itr<<"\t"<<ConvertUtf8ToGBK(*itr)<<"\t"<<IsTextUTF8((*itr).c_str(),(*itr).size())<<"\t"<<IsTextUTF8(*itr)<<"\n";
	}

	std::cout<<"--------------gbk--->utf8----------------\n";
	for (std::vector<std::string>::iterator itr = gVecStr.begin();itr!=gVecStr.end();++itr)
	{
		std::cout<<*itr<<"\t"<<ConvertGBKToUtf8(*itr)<<"\t"<<IsTextUTF8((*itr).c_str(),(*itr).size())<<"\t"<<IsTextUTF8(*itr)<<"\n";
	}

	std::cout<<"---------------------------------\n";
	system("pause");
	return 0;
}