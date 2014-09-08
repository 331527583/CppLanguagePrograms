#include <iostream>
#include <vector>
#include <algorithm> //heap�㷨ͷ�ļ�
using namespace std;
//heap��������STL��������ȷ��priority_queue�ڲ�ʵ�֡�
//heap��һ����ȫ����������Ҷ�ڵ��⣬���нڵ㶼��ȫ�������ġ�Ҷ�ڵ㰴��������Ҳ��������
//heap���ṩ�������ܣ�Ҳû�е�����

void print_vec_int(const vector<int>& vec)
{
	for (size_t i=0; i<vec.size(); i++)
		cout<<vec[i]<<" ";
	cout<<"\n";
}
int main()
{
	int ia[9] = {0,1,2,3,4,8,10,3,5};
	
	
	{
		// ������vector��Ϊ����
		vector<int> ivec(ia,ia+9);

		print_vec_int(ivec);

		make_heap(ivec.begin(),ivec.end());
		print_vec_int(ivec);

		ivec.push_back(7);
		push_heap(ivec.begin(),ivec.end());
		print_vec_int(ivec);

		pop_heap(ivec.begin(),ivec.end());
		cout<<ivec.back()<<"\n";		//return 9�����ǲ����Ƴ�9
		ivec.pop_back();		//no return���Ƴ� 9 
		cout<<ivec.back()<<"\n"; //������pop_heap
		print_vec_int(ivec);

		sort_heap(ivec.begin(),ivec.end());
		print_vec_int(ivec);
	}

	{
		// ������������Ϊ����
		make_heap(ia,ia+9); //��Ϊ�����޷��ı��С����˲��ܽ���push_heap����

		sort_heap(ia,ia+9); //����֮�󣬲����Ǹ��Ϸ���heap
		for(int i=0;i<9;i++)
			cout<<ia[i]<<" ";
		cout<<"\n";

		//��������һ��heap
		make_heap(ia,ia+9);

		pop_heap(ia,ia+9);
		cout<<ia[8]<<"\n";
	}
	system("pause");
	return 0;
}