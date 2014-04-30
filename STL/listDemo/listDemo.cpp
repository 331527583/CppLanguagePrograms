#include<iostream>
#include<list>
#include<string>
#include<algorithm>
using namespace std;

class A
{
public :
	int k;
	A(int i=100):k(i){}
};
//һԪν��
class Initial : public unary_function<char,bool>
{
	char chr;
public:
	explicit Initial(char c):chr(c){}
	bool operator()(const string& str)const { return str[0] == chr ;}
};
//��Ԫν��
class bi_list_equal : public binary_function<const string&,const string&,bool>
{
	char chr;
public:
	explicit bi_list_equal(char c):chr(c){}
	bool operator()(const string& s1,const string& s2)const
	{
		return s1[0]== s2[0] && s1[0] == chr;//???
	}
};
void print(const list<string>& li)
{
	cout<<li.size()<<" : ";
	list<string>::const_iterator iter;
	for( iter = li.begin(); iter != li.end(); iter++ )
		cout << *iter<<"\t";
	cout<<endl;
}

void test_unique()
{
	list<int> listint;
	listint.push_back(1);
	listint.push_back(2);
	listint.push_back(2);
	listint.push_back(3);
	listint.push_back(3);
	listint.push_back(3);
	listint.push_back(4);
	listint.push_back(6);
	list<int>::iterator first = listint.begin();
	list<int>::iterator last  = listint.end();
	list<int>::iterator next  = first;
	//unique
	while( ++next != last)
	{
		if( *first == *next)
			next = listint.erase(next);
		else
			first = next;

		next = first;
	}

	list<int> listint2;
	listint2.push_back(10);
	listint2.push_back(100);
	listint2.push_back(2);
	listint2.push_back(12);
	listint2.push_back(3);

	//listint.merge(listint2);
	cout<<"----------------------\n";
}
int main()
{
	test_unique();
	//-----------------------------------
	list<A*> li; //���ʹ�� list<A*>* pli;���������ʹ��ǰ��ʼ��pli��pli=NULL
	A *a = new A(7);
	A *aa = new A;
	li.push_back(a);
	li.push_back(aa);
	cout<<"size = "<<li.size()<<endl;
	li.erase(li.begin());  //ɾ��list��ָ�벢��Ӱ��ԭָ�룬ԭָ��a��Ȼ���ڿ��Է���
	cout<<"size = "<<li.size()<<endl;
	cout<<a->k<<endl;
	delete a;  //ɾ��ָ�����list�е�ָ��ʧЧ����Ϊ��ָָ��a�ѱ�ɾ��
	cout<<"size = "<<li.size()<<endl;
	cout<<a->k<<endl;
	for(list<A*>::iterator ite = li.begin();ite!=li.end();ite++)
		cout<<"list : "<<(*ite)->k<<endl;
	cout<<"-----------------------------------"<<endl;

	list<string> fruit;
	list<string> citrus;
	fruit.push_back("apple");
	fruit.push_back("pear");
	citrus.push_back("orange");
	citrus.push_back("grapefruit");
	citrus.push_back("lemon");
	list<string> citrusTmp(citrus);

	print(fruit);
	print(citrusTmp);
	cout<<"-----------------------------------"<<endl;

	list<string>::iterator p = find_if(fruit.begin(),fruit.end(),Initial('p'));//����һ��ָ���һ��string����ĸ�ǡ�p���ĵ�����
	fruit.splice(p,citrusTmp,citrusTmp.begin());//��citrusTmp�ĵ�һ��Ԫ����ӵ� p֮ǰ��citrusTmp�ĵ�һ��Ԫ�ؽ���citrusTmpɾȥ
	print(fruit);
	print(citrusTmp);
	cout<<"-----------------------------------"<<endl;

	fruit.splice(fruit.end(), citrusTmp);//��citrusTmp������Ԫ����ӵ�fruit��(��ӵ���һ������֮ǰ)��֮��citrusTmp��Ԫ��Ϊ��
	print(fruit);
	print(citrusTmp);
	cout<<"-----------------------------------"<<endl;

	citrusTmp = citrus;
	fruit.sort();
	citrusTmp.sort();
	fruit.merge(citrusTmp);
	print(fruit);
	print(citrusTmp);
	cout<<"-----------------------------------"<<endl;

	fruit.remove("orange");//ɾ��������orange��Ԫ��
	print(fruit);
	cout<<"-----------------------------------"<<endl;

	fruit.remove_if(Initial('l'));//ɾ�����п�ͷ����ĸl��Ԫ��
	print(fruit);
	cout<<"-----------------------------------"<<endl;

	fruit.sort();
	fruit.unique(bi_list_equal('g'));//ɾ����ͷ����ĸp���ظ�Ԫ��,
	print(fruit);

	fruit.unique();//��������ɾ�������ظ�Ԫ�أ�֮����Ҫ����������Ϊuniqueֻ��ɾ�������ظ���Ԫ��
	print(fruit);
	cout<<"-----------------------------------"<<endl;

	system("pause");
	return 0;
}