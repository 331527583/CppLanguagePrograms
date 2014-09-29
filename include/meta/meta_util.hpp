// ***********************************************************************
// Filename         : meta_util.hpp
// Author           : LIZHENG
// Created          : 2014-09-29
// Description      : 
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-09-29
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_METAUTIL_HPP
#define ZL_METAUTIL_HPP

//�ж������Ƿ���POD
template <typename T>
struct must_be_pod
{
	~must_be_pod()
	{
		void(*p)() = constraints;
	}
private:
	static void constraints()
	{
		union
		{
			T   T_is_not_POD_type;
		};
	}
};
template <>
struct must_be_pod < void >
{

};

//�ж����������Ƿ�����ͬһ���̳���ϵ������public�̳�
template< typename Derived, typename Base >
struct must_have_inherit
{
	~must_have_inherit()
	{
		void(*p)(Derived*, Base*) = constraints;
	}
private:
	static void constraints(Derived* pd, Base* pb)
	{
		pb = pd;
	}
};

//�ж������Ƿ��ṩ���±���ʲ���
template< typename T>
struct must_be_subscriptable 
{
	must_be_subscriptable()
	{
		void(*p)(const T&) = constraints;
	}
private:
	static void constraints(const T& T_is_not_subscriptable)
	{
		sizeof(T_is_not_subscriptable[0]);
	}

};

//�ж������Ƿ��ṩ���±���ʲ��������Ҹ�������ԭ��֧�ֶ���������operator[]��
template <typename T>
struct must_be_subscriptable_as_decayable_pointer  
{
	must_be_subscriptable_as_decayable_pointer()
	{
		void(*p)(const T&) = constraints;
	}
private:
	static void constraints(T const &T_is_not_decay_subscriptable)
	{
		sizeof(0[T_is_not_decay_subscriptable]); // ����������ԭ��ָ��
	}
};

//�ж����������Ƿ���ͬ����С��
template< typename T1, typename T2 >
struct must_be_same_size
{
	must_be_same_size()
	{
		void(*p)() = constraints;
	}
private:
	static void constraints()
	{
		const int T1_not_same_size_as_T2 = (sizeof(T1) == sizeof(T2));
		int       arr[T1_not_same_size_as_T2];
	}
};

template <typename T1>
struct must_be_same_size<T1, void>
{};
template <typename T2>
struct must_be_same_size<void, T2>
{};
template <>
struct must_be_same_size<void, void>
{};

#endif  /* ZL_METAUTIL_HPP */