#include <iostream>

/*
sizeof()��strlen()������

1. sizeof��C++�е�һ���ؼ��֣���strlen��C�����е�һ��������
2. sizeof������ֽڳ��ȣ���strlen���ȴ��ʵ�ʳ��ȣ�
3. sizeof�����ϵͳ������ڴ���������strlenͨ������'\0'ʱ��������ֵ����
3  sizeof���������κ��ࡢ�ṹ�塢���󡢱��������͵����ϣ�strlenͨ���������ַ�������;
4. sizeof�ڼ���һ�������ͻ������ĵĴ�Сʱ����Ҫ���������ݳ�Ա���ڴ沼�֣����������ܻᱣ���ڴ���룩��
5. sizeof���ڱ����ڼ���ģ���strlen��������ʱ�����,Ҳ���sizeof�������������ͣ��������ʹ��sizeof��ģ���̡�Ԫ����д����ʣ�
*/

class C;

//����BoostԴ�룬����ȫ���ָ��ɾ��
template<class T> inline void checked_delete(T *x)
{
	typedef char type_must_be_complete[ sizeof(T) ? 1 : -1]; // ���T�����������ͣ���˾�������
	(void) sizeof(type_must_be_complete);
	delete x;
}

class A
{
private:
	int    num;
	double score;
	char   ch;
};

class B
{
private:
	char   ch;
	int    num;
	double score;
};


int main()
{
	int i = 1;
	std::cout << sizeof(i) << "\n";   //sizeof(i) == sizeof(int) == 4
	
	char str1[] = "hello world";
	std::cout << sizeof(str1) << "\t" << strlen(str1) << "\n"; //12 11, ǰ������ΪΪstr1�ܹ�������12���ֽڴ�С�ڴ棨���Ͻ�����'\0'��,��strlen����ʱ�������Ͻ�����

	char str2[100] = "hello world";
	std::cout << sizeof(str2) << "\t" << strlen(str2) << "\n"; //100 11, ǰ������Ϊ��str2��ʽ������10���ֽڴ�С�ڴ�,��strlen�������ʵ�ʳ��ȣ������û��ʹ�ã�

	char *str3 = "hello world";
	std::cout << sizeof(str3) << "\t" << strlen(str3) << "\n"; //4 11, ǰ������Ϊstr��һ��ָ�룬ͨ��һ��ָ���С��int�Ĵ�С����4�ֽ�

	A a;
	std::cout << sizeof(a) << "\t" << sizeof(A) << "\n"; //24 24, sizeof(a) == sizeof(A) == 8+8+8 == 24, �ڴ����

	A *b = new A;
	std::cout << sizeof(b) << "\t" << sizeof(*b) << "\n"; //4 24, sizeof(b) == sizeof(int) == 4, b��һ��ָ��

	std::cout << sizeof(A) << "\t" << sizeof(B) << "\n"; //24 16��sizeof(A) == 8+8+8 == 24, sizeof(B) == 1+4+(3)+8 == 16,�����е�3��ʾΪ�˶����ʣ���3���ֽ�

	C * c = NULL;
	//checked_delete(c);  //����ʧ�ܣ���ΪC�ǲ��������ͣ�ֻ��������û�ж���
	
	system("pause");
	return 0;
}

/***
�����
4
12      11
100     11
4       11
24      24
4       24
24      16
***/