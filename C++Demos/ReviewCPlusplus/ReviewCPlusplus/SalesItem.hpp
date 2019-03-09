//
//  SalesItem.hpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/11.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef SalesItem_hpp
#define SalesItem_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include "SalesPocket.hpp"

extern const double ratio;

class SalesPocket;

void globalTestFun() ;

SalesItem operator + (const SalesItem& item1,const SalesItem& item2); // it must be a friend fun of class SalesItem

ostream& operator<<(ostream&,const SalesItem& item); // the output operator must be a non member func

class SalesItem : public std::string
{
    //friend class SalesPocket; // friend class
    friend void SalesPocket::showItemsPrice()const; // friend class member function,every overloaded function should be declared obviously if it suppose to be a friend member function
    friend void globalTestFun(); // friend global member function
    typedef int index; //the redefined type is not care about access control
    
    friend SalesItem operator + (const SalesItem& item1,const SalesItem& item2);
    
    friend ostream& operator<<(ostream&,const SalesItem& item);
    
private:
    
    std::string isbn;
    unsigned units_sold;
    double revenue;
    mutable int age; // mutable variable will igonre const
    double &refVar;
    const int length;
    
    static double sex; // static member variable is better than global static variable, it obeys the class's access permission !
    
    const static double grade; // const static and the implementation is in class implementation area
    
    constexpr static const double grade1 = 2; // we could initialize the const static member variable at declaration
    
    static void staticFunction() ; // the static function can't be a const function , just like the global function
    // const function is unique to the class member function alone ,and the static fun is not a member fun absolutely,
    // so the member function can't be accessed by a this pointer, it also can't be declared as a virtual fun
    
public:
    
    void test() const;
    void test(); //overloaded function bases on function const mark
    void test2();
    void test2(int m);
    void test2(const std::string &n); //const 可以用于函数重载区分
    void test2(std::string &n);
    index test3();
    explicit SalesItem(double revenue=2); // this explicit function should be called explicitly
    //explicit SalesItem() const; // contructor with const mark is not illegal
    SalesItem(const SalesItem& item); // copy-initialization member function
    
    ~ SalesItem(); // destructor , the default destructor will execute even though we declare our destructor
    
   /* explicit*/ SalesItem(const std::string &str);
    void testSameObj(const SalesItem &param)const;
    
    SalesItem& operator = (const SalesItem& item); // assignment operator
    
    int operator[](const size_t);
    const int operator[](const size_t) const;
    
    int& operator*();
    const int& operator*()const;
    int* operator->();
    const int* operator->()const;
    
    SalesItem& operator++(); // prefix operator
    SalesItem operator++(int); // postfix operator return a new class obj
    SalesItem& operator--(); //
    SalesItem operator--(int);
    
    SalesItem& operator()(); // call operator,u can expand func params, sometimes it can simplify the complexity of func
    // for example count_if , c++ premier 450
    
    SalesItem operator + (const SalesItem& item) //add operator return a new class obj
    {
        return SalesItem();
    }
    
    SalesItem& operator += (const SalesItem& item) //add and assignment operator return this
    {
        return *this;
    }
    
    
    
};

// example




#endif /* SalesItem_hpp */
