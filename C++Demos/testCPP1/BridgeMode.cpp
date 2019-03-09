//
//  BridgeMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "BridgeMode.h"

void testBridge()
{
    OS *o1 = new WindowOS;
    OS *o2 = new LiunxOS;
    Computer *c1 = new AppleComputer;
    Computer *c2 = new HPComputer;
    c1->InstallOS(o1);
    c2->InstallOS(o2);
}
