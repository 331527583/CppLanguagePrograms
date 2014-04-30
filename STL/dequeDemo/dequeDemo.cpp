//deuqe:˫�˶��С��������˵Ĳ���Ч��������list�����±�������нӽ�vector��Ч��
//	  ���dequeһ��������Щ��Ҫ�����˼����ɾ���ĵط�
//	  deque�󲿷ֲ���������vector ��list
#include <iostream>
#include <deque>
using namespace std;

void printDeque(deque<int> d)
{
	//ʹ���±�
	//for (unsigned int i = 0; i < d.size(); i++)
	//{
	// cout<<"d["<<i<<"] = "<<d[i]<<", ";
	//}

	//ʹ�õ�����
	//deque<int>::iterator iter = d.begin();
	//for (;iter != d.end(); iter ++)
	//{
	// cout<<"d["<<iter-d.begin()<<"] = "<<(*iter)<<", ";
	//}

	//ʹ�õ�����ָ��
	deque<int>::iterator *pIter = new deque<int>::iterator;
	if ( NULL == pIter )
		return ;

	for (*pIter = d.begin(); *pIter != d.end(); (*pIter)++)
		cout<<"d["<<*pIter - d.begin() <<"]="<<**pIter<<", ";

	if (NULL != pIter)
	{
		delete pIter;
		pIter = NULL;
	}
	cout<<endl;
}

template <class T>
class print_obj
{
public:
	void operator () (T& t)
	{
		cout << t << " ";
	}
};

int main()
{
	//------------------------------splice---------------------------------

	//����deque
	deque<int> d1; //����һ��û���κ�Ԫ�ص�deque����
	deque<int> d2(10);//����һ������10��Ԫ�ص�deque����ÿ��Ԫ��ֵΪĬ��
	deque<double> d3(10, 5.5); //����һ������10��Ԫ�ص�deque����,ÿ��Ԫ�صĳ�ʼֵΪ5.5
	deque<double> d4(d3); //ͨ������һ��deque�����Ԫ��ֵ, ����һ���µ�deque����
	int iArray[] = {11, 13, 19, 23, 27};
	deque<int> d5(iArray, iArray+5);//������������[first, last)��ָ��Ԫ�ؿ�����һ���´�����deque������

	//��ʼ����ֵ��ͬvectorһ��,ʹ��β�����뺯��push_back()
	for (int i = 1; i < 6 ; i++)
		d1.push_back(i*10);
	//����Ԫ��: 1-�±귽ʽ 2-��������ʽ ����������ԣ�
	cout<<"printDeque(d1) : "<<endl;
	printDeque(d1);

	//Ԫ�ز��룺β��������push_back()��ͷ��������push_front()������λ�ò�����insert(&pos, elem)
	cout<<"d1.push_front(100): "<<endl;
	d1.push_front(100);
	printDeque(d1);
	cout<<"d1.insert(d1.begin()+3, 200): "<<endl; //֧�������ȡ(��[]������)������begin()����+3
	d1.insert(d1.begin()+2,200);
	printDeque(d1);

	//Ԫ��ɾ�� β��ɾ����pop_back();ͷ��ɾ����pop_front();
	//�������λ�û���������ϵ�Ԫ��ɾ����erase(&pos)/erase(&first, &last)��ɾ������Ԫ����clear();
	cout<<"d1.pop_front(): "<<endl;
	d1.pop_front();
	printDeque(d1);

	cout<<"d1.erase(d1.begin()+1): "<<endl;
	d1.erase(d1.begin()+1); //ɾ����2��Ԫ��d1[1]
	printDeque(d1);

	cout<<"d1.erase(d1.begin(), d1.begin() + 2) = "<<endl;
	d1.erase(d1.begin(), d1.begin() + 2);
	printDeque(d1);

	cout<<"d1.clear() :"<<endl;
	d1.clear();
	printDeque(d1);

	//��������
	cout<<"���������÷�: "<<endl;
	int flag = 0;
	while(flag < 2)
	{
		if (0 == flag )
		{
			for (int i = 1; i < 6 ; i++) //�ָ�
				d1.push_back(i*10);
		}
		else
		{
			d1.clear();
			cout<<"after d1.clear() , d1.front(), d1.back() is abnormal! other info.:"<<endl;
		}
		cout<<"d1.empty() = "<<d1.empty()<<endl;
		cout<<"d1.size() = "<<d1.size()<<endl;
		cout<<"d1.max_size() = "<<hex<<d1.max_size()<<endl;
		if (!d1.empty())
		{
			cout<<"d1.front() = "<<d1.front()<<endl;
			cout<<"d1.back() = "<<d1.back()<<endl;
		}

		flag++;
	}

	//����
	cout<<"d1.swap(d5)= "<<endl;
	d1.swap(d5);
	cout<<"d1 = ";
	printDeque(d1);
	cout<<"d5 = ";
	printDeque(d5);
	//printDeque(d)

	system("pause");
	return 0;
}

//˵��
//#include <deque>deque��������vector���ƣ�֧��������ʺͿ��ٲ���ɾ��������������ĳһλ���ϵĲ��������ѵ�������ʱ�䡣
//��vector��ͬ���ǣ�deque��֧�ִӿ�ʼ�˲������ݣ�push_front()��
//���죺
//	deque<Elem> c ����һ���յ�deque ����deque<Elem> c1(c2) ����һ��deque�� ����
//	deque<Elem> c(n) ����һ��deque������n�����ݣ����ݾ���ȱʡ��������� ����
//	deque<Elem> c(n, elem) ����һ������n��elem������deque ����
//	deque<Elem> c(beg,end) ����һ����[beg;end)�����deque ����
//	c.~deque<Elem>() �����������ݣ��ͷ��ڴ�
//������
//	c.assign(beg,end) ��[beg; end)�����е����ݸ�ֵ��c�� ��
//	c.assign(n,elem) ��n��elem�Ŀ�����ֵ��c�� ����
//	c. at(idx) ��������idx��ָ�����ݣ����idxԽ�磬�׳�out_of_range�� ����
//	c.back() �������һ�����ݣ��������������Ƿ���ڡ� ����
//	c.begin() ���ص������صĿ�һ�����ݡ� ����
//	c.clear() �Ƴ��������������ݡ� ����
//	c.empty() �ж������Ƿ�Ϊ�ա� ����
//	c.end() ָ��������е����һ�����ݵ�ַ�� ����
//	c.erase(pos) ɾ��posλ�õ����ݣ�������һ�����ݵ�λ�á� ����
//	c.erase(beg,end) ɾ��[beg,end)��������ݣ�������һ�����ݵ�λ�á� ����
//	c.front() ���ص�һ�����ݡ� ����
//	get_allocator ʹ�ù��캯������һ�������� ����
//	c.insert(pos,elem) ��posλ�ò���һ��elem����������������λ�� ����
//	c.insert(pos,n,elem) ��posλ�ò���>n��elem���ݡ��޷���ֵ ����
//	c.insert(pos,beg,end) ��posλ�ò�����[beg,end)��������ݡ��޷���ֵ ����
//	c.max_size() ����������������ݵ������� ����
//	c.pop_back() ɾ�����һ�����ݡ� ����
//	c.pop_front() ɾ��ͷ�����ݡ� ����
//	c.push_back(elem) ��β������һ�����ݡ� ����
//	c.push_front(elem) ��ͷ������һ�����ݡ� ��
//	c.rbegin() ����һ��������еĵ�һ�����ݡ� ����
//	c.rend() ����һ��������е����һ�����ݵ���һ��λ�á� ����
//	c.resize(num) ����ָ�����еĳ��ȡ� ����
//	c.size() ����������ʵ�����ݵĸ����� ����
//	c.swap(c2) ����
//	swap(c1,c2) ��c1��c2Ԫ�ػ�����