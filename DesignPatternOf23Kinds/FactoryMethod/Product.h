//Product.h
#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include "Product.h"
#include<iostream>
using namespace std;

class Product
{
public:
    virtual ~Product() = 0 {	};
protected:
    Product() {}
};

class ConcreteProduct: public Product
{
public:
    ConcreteProduct()
    {
        cout << "ConcreteProduct...." << endl;
    }
    ~ConcreteProduct() {	}

    //�Լ���ӣ�������������ת��
    void test()
    {
        cout << "ConcreteProduct--test" << endl;
    }
};

#endif //_PRODUCT_H_ 

