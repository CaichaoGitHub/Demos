//
//  Operator.hpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/20.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef Operator_hpp
#define Operator_hpp

#include <stdio.h>
#include <string>

using namespace std;

//
class GTS
{
    int bound;
public:
    GTS(int var = 0):bound(var){}
    bool operator()(const string &str) // call operator
    {
        return str.size() > bound;
    }
};

void testOperatorCall();

void testFunctionObject();

void testFunctionAdapter();

void testConversionOperator();

#endif /* Operator_hpp */
