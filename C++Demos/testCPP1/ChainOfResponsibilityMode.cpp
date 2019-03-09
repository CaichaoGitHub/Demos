//
//  ChainOfResponsibilityMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "ChainOfResponsibilityMode.h"

void testChainOfResponsibility()
{
    Manager *g = new GeneralManager(NULL,"A");
    Manager *m = new Majordomo(g,"B");
    Manager *c = new CommonManager(m,"C");
    c->DealWithRequest("D", 300);
    c->DealWithRequest("D", 600);
    c->DealWithRequest("D", 1000);
    delete g;
    delete m;
    delete c;
}