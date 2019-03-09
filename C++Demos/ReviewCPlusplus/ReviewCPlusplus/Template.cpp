//
//  Template.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/11/2.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "Template.hpp"
#include <iostream>

using namespace std;

//template <typename T1>
//void template1(T1 param1 ,T1 param2)
//{
//    cout << "param is " << param1 << ends << param2 << endl;
//}




void templateFriendFun()
{
    ScreenT<char> ss,nn;
    ScreenT<int> mm;
    
    //ScreenT<char>::staticM = 1;
    
    ss.staticM = 2; //
    mm.staticM = 3;
    
    cout << "static variable of template " << ss.staticM << "\t" << nn.staticM << "\t" << mm.staticM << endl;
}

template <typename T>
int ScreenT<T>::staticM = 1; // before we use the static variable,we should initialize the static variable

void testtest()
{
    ScreenT<char>::staticM = 1;
}

template<> // the specified version of template
bool compareN(const char &m,const char &n)
{
    return true;
}

//template<typename Type> template <>
//void ScreenT<Type>::assign(const char &n)
//{
//    
//}


