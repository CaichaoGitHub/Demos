//
//  SalesItem.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/11.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "SalesItem.hpp"

const double ratio = 0;

void globalTestFun()
{
    SalesItem::sex = 1;
    SalesItem item;
    item.revenue;
    
    SalesItem itemArray[] = {SalesItem(),SalesItem()}; // copy-initialization
    
    //using add operator
    
    operator+(itemArray[0],itemArray[1]);
    
    itemArray[1] + itemArray[0];
    
    itemArray[0] += itemArray[1];
    
    itemArray[0].operator+=(itemArray[1]);
    
}

double SalesItem::sex = 1; // implement the static member variable directly

const double SalesItem::grade = 1; // implement the static const member variable directly

SalesItem operator + (const SalesItem& item1,const SalesItem& item2)
{
    return SalesItem();
}

ostream& operator<<(ostream& os,const SalesItem& item)
{
    return os;
}

//常量成员函数
void SalesItem::test() const //const 函数不能修改内部值 this 指针为 const SalesItem* 所以不能修改任何值
{
    //this->revenue = 2; //不能修改任何值
    
    this->age = 1;       // const method can still modify mutable variable
    
    if (this->revenue) //只能访问
    {
        
    }
    
    this->sex = 0;
}

void SalesItem::staticFunction() // implement the static member function
{
    // there is no need to specily static mark at the static function implementation
    // 
}

void SalesItem::test()
{
    
}

void SalesItem::test2()
{
    this->test();
}

void SalesItem::test2(int m)
{
    
}

void SalesItem::test2(const std::string &n)
{
    
}

void SalesItem::test2(std::string &n)
{
    
}



void test()
{
    const SalesItem item{}; // const 对象只能调用const 函数 非const函数无法调用
    item.test();
    //item.test2();
    
    SalesItem item2;
    item2.test2();
    item2.test(); //非const对象可以调用const函数
    
}


SalesItem::SalesItem(double revenue):revenue(revenue),age(0),refVar(revenue),length(0),std::string() //构造函数,the reference variable should be initialized on class object initialization,初始化列表初始化顺序和定义顺序一样
// 如果对象没有默认构造函数，也需要在初始化列表中指定对象的初始化
{
    
}

SalesItem::SalesItem(const SalesItem& item):refVar(item.refVar),length(0)
{
    
}

SalesItem::~SalesItem()
{
    
}

SalesItem::index SalesItem::test3() // we shoud use the inner type with :: as the return type
{
    return ::ratio; // we can use :: to access global variable
}

int m =0;
double n = 0;

SalesItem::SalesItem(const std::string &str):refVar(n),length(m)
{
    return;
}


void SalesItem::testSameObj(const SalesItem &param) const
{
    return ;
}


SalesItem& SalesItem::operator=(const SalesItem &item)
{
    return *this;
}

