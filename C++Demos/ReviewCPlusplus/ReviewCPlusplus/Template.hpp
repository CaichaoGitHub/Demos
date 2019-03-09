//
//  Template.hpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/11/2.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef Template_hpp
#define Template_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

template <typename T0>
void template0(const T0 &param1 ,const T0 &param2)
{
    cout << "param is " << param1 << ends << param2 << endl;
}

template <typename T1>
void template1(T1 param1 ,T1 param2)
{
    cout << "param is " << param1 << ends << param2 << endl;
}


typedef double T2;
template <class T2> // the template t2 will cover the global t2
void template2(T2 param) // typename is equal to class in template
{
    //T2 tmp = 1;
    
   // typedef int T2; conflict with the template t2
}

template <typename T3>
void template3(T3 pp)
{
    typename T3::size m; // if the T3 type is class and it has a inner type of size , we can use the type like this
}

// its legal to using a active type in template

template <typename T4 , int N>
void template4(T4 m)
{
    cout << "param is " << m << "\t the constant is " << N << endl;
}

template <typename T5>
int compareTemplate(T5 &a , T5 &b)
{
    return 0;
}

template<typename T6,typename T7,typename T8>
T6 sumtemplate(const T7 &m,const T8 &n) // the match order is from left to right,in this case , we need to point out the type of t6 sumtemplate<int>
{
    return (m + n);
}

template<typename T6,typename T7,typename T8>
T8 sumtemplate2(const T7 &m,const T6 &n) // in this case , we have to point out all of types sumtemplate2<int,double,int>
{
    return (m + n);
}

template<typename TX>
bool compareN(const TX &m,const TX &n)
{
    return true;
}

template<> // the specified version of template
bool compareN(const char &m,const char &n); // its not like the template , we can only declare the method in head and define the method in source file

template <typename Ttt>
class FClass {
    
    
public:
    
};

void templateFriendFun();

template <typename Type>
class ScreenT {
    
    Type *t;
    
    friend void templateFriendFun();
    friend void fun();
    friend class fClass; // not template class or func,class and fun can be ScreenT's friend
    
    template<typename TT> friend class FClass;
    template<typename TTt> friend void ff(const TTt&); // template class or func,all of class ,any type,can be ScreenT's friend
    
    friend class FClass<char> ; // specified class or func, only the specified class or fun can be ScreenT's friend
    friend int sumtemplate<int,int,int>(const int &m,const int &n);
    
    friend class FClass<Type>; // the most useful style
    
    
    
public:
    
    template <typename NT> // the tempate member class
    void assign(const NT &n)
    {
        
    }
    
//    template <>
//    void assign(const char &n);
    
    
    static int staticM; // every type of template class has a static variable
    
    
};


#endif /* Template_hpp */
