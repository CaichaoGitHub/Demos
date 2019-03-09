//
//  CPPNewFeature.cpp
//  testCPP1
//
//  Created by Caichao on 14/12/19.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "CPPNewFeature.h"


void testCPPNewFeature()
{
    auto sharePtr = std::make_shared<TestEnableShareFromThis>();
    sharePtr->testEnableShareFromThis();
}