//
//  Operator.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/20.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "Operator.hpp"
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <functional>

bool GT6(const string&str)
{
    return str.size() > 6;
}

void testOperatorCall()
{
    vector<string> vec;
    
    count_if(vec.begin(), vec.end(), GTS(6)); // count_if will go through the vec and call GTS for every element of vec
    // we have overloaded the call operator ,so count_if call the GTS call operator actually!
    //if we use a simple func, we would not be so simple to use the count_if
    
    count_if(vec.begin(), vec.end(), GTS(2));
    
    count_if(vec.begin(), vec.end(), GT6); // simple predicative method
    
}

void testFunctionObject()
{
    //all standard function objects' implementation depending on the call operator -> operator()
    //all of functon objects have a widely use of standard algorithms
    
    plus<int> addOperator; // it implements the call operator
    
    cout << "addOperator:" << addOperator(10,11) << endl;
    
    negate<int> negateOperator;
    
    cout << "negateOperator:" << negateOperator(10) << endl;
    
    vector<int> vec = {1,4,2,3};
    
    sort(vec.begin(), vec.end(), greater<int>());
    
    cout << vec[0] << vec[1] << vec[2] << vec[3] << endl;
    
}

void testFunctionAdapter()
{
    vector<int> vec = {11,42,2,3,11};
    
    
    cout << count_if(vec.begin(), vec.end(), bind1st(less_equal<int>(), 10)) << endl;
    
    
    cout << count_if(vec.begin(), vec.end(), bind2nd(less_equal<int>(), 10)) << endl;
    
    
    cout << count_if(vec.begin(), vec.end(), not1(bind2nd(less_equal<int>(), 10))) << endl;
    
    //cout << count_if(vec.begin(), vec.end(), not2(bind2nd(less_equal<int>(), 10))) << endl;
    
}

class SmallInt {
    int val;
    
public:
    
    SmallInt(int i = 0):val(i)
    {
        if (i < 0 || i > 255)
        {
            throw std::out_of_range("out of range");
        }
    }
    
    // conversion operator
    operator int()const // this is a bad design of conversion operator , sometimes it will conflict with the constructor which accepts a int type param
    {
        return val;
    }
    
    SmallInt& operator+(const SmallInt&val)
    {
        return *this;
    }
    
    
};

class Integral { // the integral has the ability of convering itself to smallint , but it can't  convert to int through two different conversions;
    int val;
    
public:
    Integral(int i = 0):val(i){}
    
    operator SmallInt(){return val;}
    
    //operator const SmallInt(){return val;} //because the result is a temp variable,so it is meaningless of converting integral to const smallint
};

void testConversionOperator()
{
    SmallInt it;
    
    it = 2; // implicity convert from int to small int ,then assign temp smallint to it
    
    if (it > 3) // call conversion operator convert smallint to int then comparing with 3
    {
        
    }
    
    int ival = static_cast<int>(it) + 3;
    
    Integral inte;
    
    SmallInt x = inte; // convert to small int
    
   // int m = inte; // failed to convert to small int
    
    
    SmallInt ai,bi;
    SmallInt c = ai+bi; // completed conversion
    //int n = c+2; ambiguous expression , firstly , the smallint can convert to int to plus 2 ,secondly ,the 2 can implicity convert to smallint and call operator + and then call conversion operator convert small int to int
    
    
}






