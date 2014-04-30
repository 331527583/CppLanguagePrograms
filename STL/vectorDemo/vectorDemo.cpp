#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <iterator>
#include <algorithm>
using namespace std;

class Num
{
	int k;
public:
	Num(){}
	Num(int i):k(i){}
	int get(){ return k;}
	~Num(){cout<<"~Num()\n";}
};
class A
{
	int i;
public:
	A():i(-1){}
	A(int ii):i(ii){}
	int get(){ return i;}
};
class Record
{
	A a;
public:
	Record(){}
	Record(int i):a(i){}
	Record(A& b):a(b){}
	int getA(){ return a.get();}
};
void testInit()
{
	vector<int> vi(2);//ǰ����Ԫ��Ĭ��Ϊint���͵�Ĭ��ֵ��0��
	vi.push_back(722);//������vi�����Ԫ�أ�
	vi.push_back(292);
	vi.push_back(822);
	cout<<vi.size()<<endl;//size =5
	for(size_t i=0;i<vi.size();i++)
		cout<<vi[i]<<"\t";

	vector<Num> vn(2);//���Numû��Ĭ�Ϲ��캯����������ʧЧ����Ϊ������Ԫ�ض�������Ĭ�Ϲ��캯����ʼ��
	vn.push_back(Num(1));
	vn.push_back(Num(2));
	vn.push_back(Num(3));
	cout<<endl<<vn.size()<<endl;
	for(size_t i=0;i<vn.size();i++)
		cout<<vn[i].get()<<"\t";//ǰ����Ԫ�ص�a��Ч����Ϊû�г�ʼ��

	vector<Record> vr(2);
	//vector<Record> vr(2,Record(5678));
	vr.push_back(Record());
	vr.push_back(Record(23));
	vr.push_back(Record(A()));
	vr.push_back(Record(A(678)));
	cout<<endl<<vr.size()<<endl;
	for(size_t i=0;i<vr.size();i++)
		cout<<vr[i].getA()<<"\t";
}
void test2DArray()
{
	vector<int> a(2);
	vector<int> arr[2];  //�൱�ڶ�λ�������ά����
	for(int i=0;i<2;i++)
		a.push_back(i+1);
	for(int i =0;i<2;i++)
		for(int j=0;j<2;j++)
			arr[i].push_back(i*10+j);

	for(size_t i=0;i<a.size();i++)
		cout<<a[i]<<'\t';
	cout<<endl;
	for(int i =0;i<2;i++)
	{
		for(size_t j=0;j<arr[i].size();j++)
			cout<<arr[i][j]<<'\t';
		cout<<endl;
	}
}
//һԪν��
class Initial : public unary_function<char,bool>
{
	char chr;
public:
	explicit Initial(char c):chr(c){}
	bool operator()(const string& str)const { return str[0] == chr ;}
};
//һԪν��
class Initial_not : public unary_function<char,bool>
{
	char chr;
public:
	explicit Initial_not(char c):chr(c){}
	bool operator()(const string& str)const { return str[0] != chr ;}
};

class find_del_preq : public unary_function<int,bool>
{
	int id;
public:
	explicit find_del_preq(int c):id(c){}
	bool operator()( int i)const { return id == i ;}
};
bool test_preq(int i)
{
	return i==4;
};
// ���
template <typename T>
class print_obj
{
public:
	void operator()(const T& t)
	{
		cout<<t<<endl;
	}
};
int main()
{
	test2DArray();
	testInit();//Ԫ�س�ʼ��������
	cout<<"\n-----------------------------------"<<endl;
	//------------------------------��ֵ---------------------------------
	vector<int> v1(10);
	v1.resize(20);
	cout<<"size = "<<v1.size()<<endl;
	v1.reserve(15);
	cout<<"size = "<<v1.size()<<endl;
	v1.assign(6,456);  //ֱ�Ӹı�Ԫvector�е�����Ԫ�ء�����ԭ��Ԫ�ض���ɾ������Ԫ�ز���
	cout<<"size = "<<v1.size()<<endl;

	vector<int> vi;
	vi.push_back(1);
	vi.push_back(2);
	vi.push_back(4);
	vi.push_back(1);
	vi.push_back(2);

	//----------------------------����-----------------------------
	vector<int>::iterator iter1 = find(vi.begin(),vi.end(),1);//��ǰ�����
	vector<int>::reverse_iterator rev_iter =find(vi.rbegin(),vi.rend(),1);//�Ӻ���ǰ�ң����ط��������
	vector<int>::iterator iter2 = --rev_iter.base();
	cout<<"\n-----------------------------------"<<endl;

	//----------------------------���-----------------------------
	vector<string> fruit;
	fruit.push_back("apple");
	fruit.push_back("pear");
	fruit.push_back("orange");
	fruit.push_back("grapefruit");
	fruit.push_back("lemon");
	fruit.push_back("pedfdr");
	fruit.push_back("psdf3r");
	vector<string> fruittmp(fruit);

	for_each(fruittmp.begin(),fruittmp.end(),print_obj<string> ());//���
	copy(fruittmp.begin(),fruittmp.end(),ostream_iterator<string>(cout,"\t"));//���
	cout<<"\n-----------------------------------"<<endl;

	//------------------------------ɾ��---------------------------------
	sort(fruittmp.begin(),fruittmp.end());	//����
	copy(fruittmp.begin(),fruittmp.end(),ostream_iterator<string>(cout,"\t"));//���
	cout<<"\n-----------------------------------"<<endl;

	vector<string>::iterator p1 = find_if(fruittmp.begin(),fruittmp.end(),Initial('p'));//�ҵ���һ������ĸp��ͷ��Ԫ�ص�����
	vector<string>::iterator p2 = find_if(p1,fruittmp.end(),Initial_not('p'));//��p1��ʼ�ҵ���һ����������ĸp��ͷ��Ԫ�ص�����
	fruittmp.erase(p1,p2);//����֮��� [p1,p2) Ԫ��
	copy(fruittmp.begin(),fruittmp.end(),ostream_iterator<string>(cout,"\t"));//���
	cout<<"\n-----------------------------------"<<endl;

	//������������Ľ����һ����
	fruittmp = fruit;
	sort(fruittmp.begin(),fruittmp.end());	//����
	vector<string>::iterator p3 = find_if(fruittmp.begin(),fruittmp.end(),Initial('p'));//�ҵ���һ������ĸp��ͷ��Ԫ�ص�����
	vector<string>::reverse_iterator rev_p4 = find_if(fruittmp.rbegin(),fruittmp.rend(),Initial('p'));//�Ӻ���ǰ�ҵ���һ������ĸp��ͷ��Ԫ�ص�����
	fruittmp.erase(p3,rev_p4.base());//����֮��� [p1,p2) Ԫ��
	copy(fruittmp.begin(),fruittmp.end(),ostream_iterator<string>(cout,"\t"));//���
	cout<<"\n-----------------------------------"<<endl;

	fruittmp.erase(fruittmp.begin());
	fruittmp.erase(find(fruittmp.begin(),fruittmp.end(),"orange"));//�˴������ܹ��ҵ���Ԫ��
	copy(fruittmp.begin(),fruittmp.end(),ostream_iterator<string>(cout,"\t"));//���
	cout<<"\n-----------------------------------"<<endl;

	//------------------------------����---------------------------------
	fruittmp.insert(fruittmp.begin()+1,"cherry");
	fruittmp.insert(fruittmp.end(),"orange");
	fruittmp.insert(fruittmp.begin()+2,fruit.begin(),fruit.end());
	copy(fruittmp.begin(),fruittmp.end(),ostream_iterator<string>(cout,"\t"));//���
	cout<<"\n-----------------------------------"<<endl;

	//------------------------------ɾ��---------------------------------
	vector<int> vecNums;
	vecNums.push_back((4));
	vecNums.push_back((6));
	vecNums.push_back((4));
	vecNums.push_back((7));
	vecNums.push_back((4));
	vecNums.push_back((1));
	//remove(vecNums.begin(),vecNums.end(),6);
	vecNums.erase(remove(vecNums.begin(),vecNums.end(),7));//ɾ��һ��Ԫ��
    vector<int>::iterator iii1 =remove_if(vecNums.begin(),vecNums.end(),find_del_preq(4)) ;//ɾ����������������Ԫ��
	//vector<int>::iterator iii2 = remove_if(vecNums.begin(),vecNums.end(),test_preq) ;//ɾ����������������Ԫ��
	vecNums.erase(iii1,vecNums.end());

	vector<Num*> vn;

	vn.assign(2,new Num(45));
	vn.push_back(new Num(23));
	vn.push_back(new Num(9));

	cout<<"\n-----------------------------------"<<endl;
	Num* nn = *(vn.begin());
	vn.erase(vn.begin());  //ֻ�Ǵ�vector�в�����Ԫ�أ�����Ԫ��ʵ������ռ���ڴ�ռ�,������ʾ����deleteɾ��
	delete nn;

	system("pause");
	return 0;
}