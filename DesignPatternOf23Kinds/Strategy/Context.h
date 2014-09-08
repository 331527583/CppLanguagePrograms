//Context.h 
#ifndef _CONTEXT_H_ 
#define _CONTEXT_H_ 

#include "Strategy.h"
class Strategy; 
/** 
*������� Strategyģʽ�Ĺؼ���Ҳ�� Strategyģʽ�� Template ģʽ�ĸ���
�������ڡ� 
*Strategy ͨ������ϡ���ί�У���ʽʵ���㷨��ʵ�֣����칹���� Template ģ
ʽ���ȡ���Ǽ̳еķ�ʽ 
*������ģʽ������Ҳ�Ǽ̳к��������ʵ�ֽӿ����õķ�ʽ������ 
*/ 
class Context 
{ 
public: 
	Context(Strategy* stg)
	{
		_stg = stg; 
	}
	~Context()
	{
		if (!_stg) 
			delete _stg;
	}
	void DoAction()
	{
		 _stg->AlgrithmInterface(); 
	}
private: 
	Strategy* _stg; 
}; 
#endif //~_CONTEXT_H_ 
