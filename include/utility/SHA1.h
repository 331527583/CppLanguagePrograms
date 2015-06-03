// ***********************************************************************
// Filename         : SHA1.h
// Author           : LIZHENG
// Created          : 2015-05-27
// Description      : ��ȫ��ϣ�㷨��Secure Hash Algorithm��
//
// Last Modified By : LIZHENG
// Last Modified On : 2015-05-27
//
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_SHA1_H
#define ZL_SHA1_H
#include <string>
#include <stdint.h>
// ���ڳ���С��2^64λ����Ϣ��SHA1�����һ��160λ����ϢժҪ�������յ���Ϣ��ʱ�������ϢժҪ����������֤���ݵ������ԡ�
// �ڴ���Ĺ����У����ݺܿ��ܻᷢ���仯����ô��ʱ��ͻ������ͬ����ϢժҪ��
// SHA1���ԣ������Դ���ϢժҪ�и�ԭ��Ϣ��������ͬ����Ϣ�������ͬ������ϢժҪ��

namespace zl
{
namespace utility
{

class SHA1
{
public:
	SHA1();
	~SHA1();

	static std::string HexDigest(const std::string& src);

public:
	void Init();
	void Update(const std::string& sp);
	// Finalizes the Sha1 operation and fills the buffer with the digest.
	//  Data is uint8_t digest_[20]
	void Final(void* digest);
	//  Hex encoding for result
	std::string HexFinal();

private:
	void SHA1Transform(uint32_t state[5], const uint8_t buffer[64]);
	void Update(const uint8_t* data, size_t input_len);
	void FinalInternal();

private:
	SHA1(const SHA1&);
	const SHA1& operator=(const SHA1&);

	struct SHA1_CTX
	{
		uint32_t state[5];
		uint32_t count[2];  // Bit count of input.
		uint8_t buffer[64];
	};

	SHA1_CTX context_;
	uint8_t  digest_[20];
};

}
}
#endif  /* ZL_SHA1_H */