// ***********************************************************************
// Filename         : LittleOrBigEndian.cpp
// Author           : LIZHENG
// Created          : 2014-05-14
// Description      : CPU��С���ж�
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-05-14
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************

#include <iostream>

int IsLittleEndian( )
{
	//Little-endianģʽ��CPU�Բ������Ĵ�ŷ�ʽ�Ǵӵ��ֽڵ����ֽڣ���Big-endianģʽ�Բ������Ĵ�ŷ�ʽ�ǴӸ��ֽڵ����ֽڡ�
	//[��С�˴洢����]: С�˷�ʽ�У�iռ���������ֽڵĳ��ȣ�,i��������ڴ���С��ַ�Ǹ��ֽ��оʹ���1�������ֽ���0.
	//��˵Ļ���1��i����ߵ�ַ�ֽڴ���ţ�char��һ���ֽڣ�����ǿ�ƽ�char����pָ��i��pָ���һ����i����͵�ַ��
	//��ô�Ϳ����ж�p�е�ֵ�ǲ���1��ȷ���ǲ���С�ˡ�
	//����������Big_endian�ģ��򷵻�0������Little_endian�ģ��򷵻�1

	//������union�Ĵ��˳�������г�Ա���ӵ͵�ַ��ʼ���
	union w {
		int i;
		char c;
	} u;
	u.i = 1;
	return(u.c ==1);
}

int  IsLittleEndianEx() 
{ 
	int i = 0x1; 
	return *(char *)&i == 0x1; 
}

int main()
{
	printf("is little endian: %d\n", IsLittleEndian());
	printf("is little endian: %d\n", IsLittleEndianEx());
	system("pause");
	return 0;
}