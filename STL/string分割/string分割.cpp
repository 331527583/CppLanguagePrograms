#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdio>
using namespace std;

void split1( string str,char chr)
{
	int num=0;

	//for (int i=0;i<str.length();i++)
	//{
	//	if (str[i]==chr)
	//	{
	//		num++;
	//		str[i]=' ';
	//	}
	//}
	num = count(str.begin(),str.end(),chr);
	replace(str.begin(),str.end(),chr,' ');
	string *array=new string[num+1];  //�ָ����ַ����ʹ���������
	stringstream ss;
	ss<<str;//�˴�str�������Կո�ֿ����ַ���
	for (int j=0;j<=num;j++)
	{
		ss>>array[j];
		cout<<array[j]<<endl;
	}
}
void split2( string str,char chr)
{
	for (size_t i=0;i<str.length();i++)
	{
		if (str[i]==chr)
		{
			str[i]=' ';
		}
	}
	istringstream iss(str); //�˴�str�������Կո�ֿ����ַ���
	while (iss)
	{
		string sub;
		iss >> sub;
		cout << sub << endl;
	}
}
//������char *strtok( char *str1, const char *str2 );
//���ܣ����������ַ���str1�н��ӡ���ǡ��Ĳ��ֵ�ָ��, �ַ���str2����Ϊ��ǵķָ���������ָ����û���ҵ�����������NULL��
//Ϊ�˽��ַ���ת���ɱ�ǣ���һ�ε���str1 ָ����Ϊ��ǵķָ�����֮�����Եĵ���str1 ��ӦΪNULL
void split3( string str,char chr)
{
	char chrs[] = "dfg|dfew|dsdfd|58568|������|4d";
	//char *chrs = str.data();
//	char delims[] = "|";
	char *delims = &chr;
	char *result = NULL;

	result = strtok( chrs, delims );
	while( result != NULL )
	{
		printf( "\"%s\"\n", result );
		result = strtok( NULL, delims );
	}
}
//���ʹ��stl���㷨��
void split4( string str,char chr)
{
	//for (int i=0;i<str.length();i++)
	//{
	//	if (str[i]==chr)
	//	{
	//		str[i]=' ';
	//	}
	//}
	replace(str.begin(),str.end(),chr,' ');
	istringstream iss1(str);
	copy(istream_iterator<string>(iss1), istream_iterator<string>(), ostream_iterator<string>(cout, "\n")); //ֱ�����

	istringstream iss2(str);
	vector<string> tokens;
	copy(istream_iterator<string>(iss2),istream_iterator<string>(),back_inserter<vector<string> >(tokens));//�洢��tokens��
}

vector<string> &split(const string &str, char delim, vector<string> &elems)
{
	stringstream ss(str);
	string item;
	while(getline(ss, item, delim))
	{
		elems.push_back(item);
		cout<<item<<endl;
	}
	return elems;
}
vector<string> split5(const string &str, char delim)
{
	vector<string> elems;
	return split(str, delim, elems);
}

vector<string> split6(const string& s, const string& delim, const bool keep_empty = true)
{
	vector<string> result;
	if (delim.empty())
	{
		result.push_back(s);
		return result;
	}
	string::const_iterator substart = s.begin(), subend;
	while (true)
	{
		subend = search(substart, s.end(), delim.begin(), delim.end());
		string temp(substart, subend);
		if (keep_empty || !temp.empty())
		{
			result.push_back(temp);
			cout<<temp<<endl;
		}
		if (subend == s.end())
		{
			break;
		}
		substart = subend + delim.size();
	}

	return result;
}
void split7(const string& str, vector<string>& tokens,const string& delimiters = " ")
{
	// Skip delimiters at beginning.
	string::size_type lastPos = str.find_first_not_of(delimiters, 0);
	// Find first "non-delimiter".
	string::size_type pos     = str.find_first_of(delimiters, lastPos);
	while (string::npos != pos || string::npos != lastPos)
	{
		// Found a token, add it to the vector.
		tokens.push_back(str.substr(lastPos, pos - lastPos));
		// Skip delimiters.  Note the "not_of"
		lastPos = str.find_first_not_of(delimiters, pos);
		// Find next "non-delimiter"
		pos = str.find_first_of(delimiters, lastPos);
	}

	for(size_t i = 0;i<tokens.size();i++)
		cout<<tokens[i]<<endl;
}
int main()
{
	string str("dfg|dfew|dsdfd|58568|������|4d");

	cout<<"---------------------split1:--------------------\n";
	split1(str,'|');

	cout<<"---------------------split2:--------------------\n";
	split2(str,'|');

	cout<<"---------------------split3:--------------------\n";
	split3(str,'|');
	//str = "dfg dfew dsdfd 58568 ������ 4d";

	cout<<"---------------------split4:--------------------\n";
	split4(str,'|');

	cout<<"---------------------split5:--------------------\n";
	split5(str,'|');

	cout<<"---------------------split6:--------------------\n";
	split6(str, "|");
	//split6(str, "|d"); //ok,��"ld"�ָ�
	//const vector<string> words = split6(str, "|");
	//copy(words.begin(), words.end(), ostream_iterator<string>(cout, "\n"));

	cout<<"---------------------split7:--------------------\n";
	vector<string> tokens;
	split7(str, tokens,"|");

	system("pause");
	return 0;
}