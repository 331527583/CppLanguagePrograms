//ǰ����裺ϵͳ���кܶ���Դ���Ƚ���Դ���༸�����ͣ�ÿһ���������м���С����
//�����С�����±������յ��ļ�����

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <Windows.h>
using namespace std;

vector<string> vecResTypes;//��Դ����
map< string,vector<string> > mapCategory; //��Դ����---��Դ����
typedef map< string,vector<string> >::iterator  MapCateIter;
typedef map< string,vector<string> >::const_iterator  CMapCateIter;
//-----------------second method-------------------
map< string, map< string,vector<string> >  > mapTotal;
typedef map< string, map< string,vector<string> >  > ::iterator  MapResIter;
typedef map< string, map< string,vector<string> >  > ::const_iterator  CMapResIter;
void init()
{
	vecResTypes.push_back("Model");
	vecResTypes.push_back("Image");
	vecResTypes.push_back("Video");
	vecResTypes.push_back("Audio");
	vecResTypes.push_back("Other");

	vector<string> category;
	category.push_back("����");
	category.push_back("����");
	category.push_back("ֲ��");
	category.push_back("����");
	mapCategory["Model"] = category;

	category.clear();
	category.push_back("����");
	category.push_back("��ľ");
	mapCategory["Image"] = category;

	category.clear();
	category.push_back("�Ƽ�");
	category.push_back("����");
	mapCategory["Video"] = category;

}

void secondinit()
{
	vector<string> vecRess;  //�������Դ��
	map< string,vector<string> > mapCate; //ĳһ�����µ�������Դ��
	vector< map< string,vector<string> > > vecType; //ĳһ�����µ�������Դ

//---------------------------------------------------------------------
	vecRess.push_back("1.xml");  
	vecRess.push_back("2.xml");
	vecRess.push_back("132.xml");
	mapCate["����"] = vecRess; //����һ�������µ������ļ���
	

	vecRess.clear();	
	vecRess.push_back("z1.xml");
	vecRess.push_back("z342.xml");
	vecRess.push_back("zw.xml");
	mapCate["ֲ��"] = vecRess;
	 
	vecRess.clear();	
	vecRess.push_back("35654.xml");
	vecRess.push_back("3dff.xml");
	vecRess.push_back("3hfgh.xml");
	mapCate["����"] = vecRess;

	mapTotal["Model"] = mapCate;  //����һ�������µ����з���
//---------------------------------------------------------------------
	vecRess.clear();
	mapCate.clear();
	vecRess.push_back("555555.xml");  
	vecRess.push_back("666666.xml");
	vecRess.push_back("777777.xml");
	mapCate["����"] = vecRess; //����һ�������µ������ļ���


	vecRess.clear();	
	vecRess.push_back("1111.xml");
	vecRess.push_back("2222.xml");
	vecRess.push_back("3333.xml");
	mapCate["��ľ"] = vecRess;	

	mapTotal["Image"] = mapCate;  //����һ�������µ����з���
//---------------------------------------------------------------------
	vecRess.clear();
	mapCate.clear();
	vecRess.push_back("zzzz.xml");  
	vecRess.push_back("aaaa.xml");
	vecRess.push_back("eeee.xml");
	mapCate["�Ƽ�"] = vecRess; //����һ�������µ������ļ���


	vecRess.clear();	
	vecRess.push_back("ggggg.xml");
	vecRess.push_back("hhhhh.xml");
	vecRess.push_back("bbbbb.xml");
	mapCate["����"] = vecRess;	

	mapTotal["Video"] = mapCate;  //����һ�������µ����з���
//---------------------------------------------------------------------
	vecRess.clear();
	mapCate.clear();
	vecRess.push_back("678678.xml");  
	vecRess.push_back("7.xml");
	 
	mapCate["����"] = vecRess; //����һ�������µ������ļ���	

	mapTotal["Audio"] = mapCate;  //����һ�������µ����з���
//---------------------------------------------------------------------
	vecRess.clear();
	mapCate.clear();
	 

	mapTotal["Other"] = mapCate;  //����һ�������µ����з���
//---------------------------------------------------------------------
}

bool addResource(const std::string& type,const std::string& category,const std::string& name)
{
	bool bflag = true;
	//std::map< std::string, std::map< std::string,std::vector<std::string> >  > mapTotal; //���ڱ�ʾ�������������Դ
	MapResIter iterType = mapTotal.find(type);
	if (iterType!=mapTotal.end())
	{
		MapCateIter iterCate = iterType->second.find(category);
		if(iterCate!=iterType->second.end())
		{
			iterCate->second.push_back(name);
		}
		else
		{
			std::vector<std::string> vecNames;
			vecNames.push_back(name);
			(iterType->second)[category] = vecNames;
		}
	}
	else
	{
		//std::map< std::string,std::vector<std::string> >::iterator  MapCateIter;
		std::map< std::string,std::vector<std::string> > mapCates;
		std::vector<std::string> vecNames;
		vecNames.push_back(name);
		mapCates[category] = vecNames;
		mapTotal[type]  = mapCates; 
	}
	return bflag;
}

string itostr(int i)
{
	std::ostringstream oss;
	std::string str1;

	oss.str( "" );
	oss << i;
	str1 = oss.str();
	return str1;
}
int main()
{
	init();

	vector<string> vecTmp;
	for(int i =0;i<vecResTypes.size();i++)
	{
		cout<<vecResTypes[i]<<":\n";
		MapCateIter iter = mapCategory.find(vecResTypes[i]);
		if(iter!=mapCategory.end() )//�ж�Ӧ����Դ����
		{
			vecTmp = iter->second;
			for(int j=0;j<vecTmp.size();j++)
			{
				cout<<"\t"<<vecTmp[j]<<endl;
			}
		}		
	}

	cout<<"------------------------second method------------------------"<<endl;
	
	//secondinit();
	DWORD starttime;
	//starttime=GetTickCount();

	srand(1);
	int times = 1000;
	for (int i = 1; i< times ; i++)
	{
		addResource(itostr(i),"cate"+itostr(rand()%times),"name"+itostr(i*10)+"");
		addResource(itostr(i),"cate"+itostr(rand()%times),"name"+itostr(i*10)+"");
		addResource(itostr(i),"cate"+itostr(rand()%times),"name"+itostr(i*10)+"");
	}
	int count = mapTotal.size();
//	starttime=GetTickCount();

	_LARGE_INTEGER time_start;    /*��ʼʱ��*/ 
	_LARGE_INTEGER time_over;        /*����ʱ��*/ 
	double dqFreq;                /*��ʱ��Ƶ��*/ 
	LARGE_INTEGER f;            /*��ʱ��Ƶ��*/ 
	QueryPerformanceFrequency(&f);  
	dqFreq=(double)f.QuadPart;  
	QueryPerformanceCounter(&time_start);  
	Sleep(1000);/*ѭ����ʱ*/ 
	 

	map< string,vector<string> > maptmp;
	for (MapResIter iter = mapTotal.begin();iter!=mapTotal.end();iter++)
	{
		cout<<iter->first<<":\n";
		maptmp = iter->second;
		for(MapCateIter cateiter = maptmp.begin();cateiter!=maptmp.end();cateiter++)
		{
			cout<<"\t"<<cateiter->first<<":\n";
			vecTmp = cateiter->second;

			for(vector<string>::iterator veciter = vecTmp.begin();veciter!=vecTmp.end();veciter++)
			{
				cout<<"\t\t"<<*veciter<<endl;
			}
		}
	}
	QueryPerformanceCounter(&time_over);  
	cout<<((time_over.QuadPart-time_start.QuadPart)/dqFreq)<<endl;//��λΪ�룬����Ϊ1000 000/��cpu��Ƶ��΢�� 
//	DWORD endtime = GetTickCount();
//	cout<<endtime - starttime<<"ms"<<endl;
	system("pause");
	return 0;
}