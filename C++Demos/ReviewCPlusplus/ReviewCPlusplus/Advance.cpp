//
//  Advance.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/11/12.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "Advance.hpp"
#include <typeinfo>
#include <iostream>

using namespace std;

class base {
    
    
public:
    virtual void test()
    {}
    
    void abc() const{cout << "yes abc is invoked" << endl;}
    
    int age;
    int sex;
};

class Derived : public base {
    
    
public:
    void test()
    {
        
    }
};


// 嵌套类

class Computer {
    
    static const int Power = 220;
    
private:
    class CPU
    {
    public:
        unsigned processCount;
        
        CPU()
        {
            cout << "the computer's CPU is invisible" << endl;
        }
        
        void print()
        {
            cout << "inner CPU and power is " << Power << endl;
        }
    };
    
public:
    
    class KeyBoard;
    
    typedef enum
    {
        ColorTypeRed,
        ColorTypeBlue
    }ColorType;
    template<ColorType CType> class Color;
    
    Computer(int m);
    
public:
    
    CPU *pCpu;
    KeyBoard *pKeyBoard;
    Color<ColorTypeRed> *pColor;
    
    union
    {
        int mInt;
        char mChar;
        
    };
    
};

class Computer::KeyBoard
{
public:
    
    void print() const
    {
        cout << "this is the computer's visible keyboard" << endl;
    }
    
    
};

template <Computer::ColorType CType>
class Computer::Color {
    
    
public:
    
    void print()
    {
        cout << "the color of the computer is " << CType << endl;
    }
    
};

Computer::Computer(int m)
{
    pCpu = new CPU;
    pKeyBoard = new KeyBoard;
    pColor = new Color<ColorTypeRed>;
}

union UnionTest { // union just like the struct
private:
    Computer com;
public:
    Computer *pCom;
    
    static int m;
    
    //Computer &pC;
    
    UnionTest()
    {
        
    }
    
};


class FileBit {
    
    
public: // 位域主要用于压缩内存，和硬件相关，例如这里定义mode只是用2位存储
    
    unsigned mode : 2;
    unsigned modified : 3;
    
};

void testAdvance()
{
    int m = 2;
    int &mRef = m;
    
    //dynamic_cast<float &>(mRef);
    
    Derived der;
    
    base &bRef = der;
    
    base *bP = &der;
    
    Derived &dRef = dynamic_cast<Derived&>(bRef);
    
    Derived *dP = dynamic_cast<Derived*>(bP);
    
    cout << "type is : " << typeid(bRef).name() << endl;
    cout << "type is : " << typeid(bP).name() << endl;
    
    cout << "type is equal : " << (typeid(bRef) == typeid(bP)) << endl; // why not equal , i don't know
    
    typedef void (*pf)(); // 普通函数指针
    pf pp = testAdvance;
    
    // 成员指针的一个用途是制作成员函数表，然后我们按需调用成员函数，即将所有的函数指针放到数据里面，然后调用
    
    int base::* pAge = &base::age; // member variable pointer
    
    typedef void (base::* pAbc)() const; // member method pointer
    
    pAbc pFunAbc = &base::abc; // get the member method pointer,获取成员函数的指针，
    
    der.abc();
    
    (der.*pFunAbc)(); //object its equal to call abc，使用成员函数指针，类似直接调用成员函数
    
    bP->abc();
    
    (bP->*pFunAbc)(); //pointer its equal to call abc
    
    int age = bP->*pAge; // get age variable
    
    
    Computer pC(1);
    
    pC.pColor->print();
    pC.pKeyBoard->print();
    pC.pCpu->print();
    pC.mInt = 1;
    
    
    
}