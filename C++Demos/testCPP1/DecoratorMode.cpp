//
//  DecoratorMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "DecoratorMode.h"

void testDecorator()
{
    Phone *p1 = new NokiaPhone("5230");
    Phone *p2 = new DecoratorPhoneA(p1);
    Phone *p3 = new DecoratorPhoneB(p2);
    p3->ShowDecorate();
    delete p1;
    delete p2;
    delete p3;
}