#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;

vector<string> vecStr;
map<string,int> modelmap;

class startWithStr
{
	string str;
public:
	startWithStr(string _str):str(_str){	}
	bool operator()()
	{

	}
};
bool myequal(string s)
{
	return s=="during";
}
class vec_str_equal : public unary_function<string,bool>
{
	string s;
public:
	explicit vec_str_equal(const string& ss) : s(ss) {	}
	bool operator()(const string& str)
	{
		return s == str;
	}
};
class map_str_equal : public unary_function<string,bool>
{
	pair<string,int> pp;
public:
	explicit map_str_equal(const pair<string,int>& _p) : pp(_p) {	}
	bool operator()(const pair<string,int>& _p)
	{
		return pp == _p;
	}
};

void readFile()
{
	ifstream  ifs("../LocalModelList.ini");
	string name;
	int option;
	assert(ifs.is_open()==true);
	while(!ifs.eof())
	{
		ifs>>name;
		vecStr.push_back(name);
		if(name == "_BEGIN_OF_MODEL_LIST_")
			break;
	}
	while(!ifs.eof())
	{
		ifs>>name>>option;
		modelmap.insert(make_pair(name,option));
		//	cout<<name<<"\t"<<option<<endl;
	}
	ifs.close();
}
void writeFile()
{
	ofstream  ofs("LocalModelList.ini");
	assert(ofs.is_open()==true);
	for (vector<string>::const_iterator iter = vecStr.begin();iter!=vecStr.end();iter++)
		ofs<<*iter<<"\t";	
	ofs<<endl<<endl;
	for (map<string,int>::const_iterator iter = modelmap.begin();iter!=modelmap.end();iter++)
		ofs<<iter->first<<"\t"<<iter->second<<endl;	
	ofs.close();
}


int main()
{	
	 
	readFile();//��ȡ�ļ�����Ϣ����ʼ��vecStr��modelmap	
//-----------------------------------vector   find-----------------------------------------------
	string vectmp = "during";
	vector<string>::const_iterator iterbegin  = find(vecStr.begin(),vecStr.end(),"Please");  //ֱ�Ӳ���
	vector<string>::const_iterator iterbegin1 = find_if(vecStr.begin(),vecStr.end(),myequal); //ʹ�ú���
	vector<string>::const_iterator iterbegin2 = find_if(vecStr.begin(),vecStr.end(),vec_str_equal("during"));//ʹ�ú�������
	for (vector<string>::reverse_iterator rev_riter = vecStr.rbegin();rev_riter!=vecStr.rend();rev_riter++)
	{
		if (*rev_riter == vectmp)
		{
			vector<string>::const_iterator viter = rev_riter.base();
		}
	}
//------------------------------------map   find----------------------------------------------
	map<string,int>::iterator iterbegin67 = find_if(modelmap.begin(),modelmap.end(),map_str_equal(make_pair("NewBld_01.xml",2)));
	string modelname = "NewBld_01.xml";
	string modelstr  = "NewBld_" ;
	map<string,int>::iterator mapiterbegin = modelmap.find(modelname); //�ҵ���һ�� modelname
	map<string,int>::iterator mapiterend;
	for (map<string,int>::reverse_iterator riter = modelmap.rbegin();riter!=modelmap.rend();riter++)
	{		
		//cout<<riter->first<<"\t"<<riter->second<<endl;		
		if(riter->first.find(modelstr)!=string::npos)	//�ҵ����һ����ͷ����modelstr��λ��	
		{
			mapiterend =  riter.base();
			break;
		}
	}
	//���������modelstr��ͷ����
	while (mapiterbegin!=mapiterend)
	{
		cout<<mapiterbegin->first<<"\t"<<mapiterbegin->second<<endl;
		mapiterbegin ++;
	}


//----------------------------------------------------------------------------------
	
//	writeFile();//������޸Ŀ��Ա��浽ԭ�ļ�

	system("pause");
	return 0;
}
