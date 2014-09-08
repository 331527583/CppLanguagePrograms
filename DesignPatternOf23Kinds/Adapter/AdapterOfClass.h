/************************************************************************/
/* ��ģʽ�� Adapter ���ü̳еķ�ʽ���� Adaptee�Ľӿڣ�
   ����ģʽ�� Adapter�в�����ϵķ�ʽʵ�� Adaptee�ĸ��� */
/************************************************************************/

#ifndef _ADAPTEROfClass_H_ 
#define _ADAPTEROfClass_H_

#include <iostream> 

class TargetOfClass
{ 
public: 
	TargetOfClass(){	} 
	virtual ~TargetOfClass(){	} 
	virtual void Request()
	{
		std::cout<<"TargetOfClass::Request"<<std::endl;
	}
}; 


class AdapteeOfClass 
{ 
public: 
	AdapteeOfClass(){	} 
	~AdapteeOfClass(){	}
	void SpecificRequest()
	{
		std::cout<<"AdapteeOfClass::SpecificRequest"<<std::endl; 
	}
}; 

class AdapterOfClass:public TargetOfClass,private AdapteeOfClass 
{ 
public: 
	AdapterOfClass(){	} 
	~AdapterOfClass(){	}
	void Request()
	{
		this->SpecificRequest();
	}
}; 


#endif //~_ADAPTEROfClass_H_ 
