//
//  ExceptionX.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/11/5.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "ExceptionX.hpp"
#include <iostream>
using namespace std;

// the base class and derived class's member function exception ,please refer C++ primer 4th at page 598

void (*pf)(int) throw (runtime_error); // the function pointer could have a description of exception

class ExceptionOne // my exception
{
public:
    ExceptionOne()
    {
        cout << "my exception class" << endl;
    }
};



class ExceptionTwo : public ExceptionOne {
    
    
public:
    ExceptionTwo()
    {
        cout << "my exception two class" << endl;
    }
};

class Boy {
    
    int grade;
    
public:
    
    Boy(int _gr):grade(_gr)
    {
        throw ExceptionTwo();
    }
    
};

class CoolBoy : public Boy{
    
    int age;
    
public:
    
    CoolBoy(int _age) // in this way,we can handle the constructor's exception
    try:Boy(2),age(_age)
    {
        
    }
    catch(ExceptionTwo &e)
    {
        cout << "yes, i catched the constructor's exception" << endl;
    }
        
};

void test1() throw(ExceptionOne)
{
    int *pInt = new int(1);
    
    auto_ptr<int> p(new int(2)); 
    
    //throw ExceptionOne();
    throw ExceptionTwo();
    
    delete pInt; //the pointr is dangerous, we could never delete the pointer if any exceptions throwed before,in case of leaking of memory ,we had better use auto_ptr  which uses the RAII(资源分配即初始化) technology
    
    *p = 2; // the pointer is safe
    
}

void test2() throw(char,ExceptionOne) // i will throw two type of exception
{
    try
    {
        test1();
    }
    catch(...)
    {
        throw ; // i can't handle the exception , so i throw it away
    }
    
    throw 'c'; // let's throw a char hahah,if test1 throw a exception, i would have no chance to throw another exception
    
}

void test3()throw(char,ExceptionOne) // if the method want throw another method's exception, it should declare it in the brackets(括号)
{
    test2(); // i don't care about any exception , so the method calling me should handle any exceptions
}
        
        
        


void testException()
{
    //CoolBoy boy(1);
    
    try
    {
        test3();
    }
    catch(ExceptionTwo &e)
    {
        cout << "yes i catch ExceptionTwo exception" << endl;
    }
    catch(ExceptionOne &e) // it's convenient to use reference param that we can handle the dynamic type of class
    {
        cout << "yes i catch ExceptionOne exception" << endl;
    }
    catch(...)
    {
        cout << "yes i catch all of exception" << endl;
    }
    
}
        
        
        


        
        
        
        
        
        
        
        



