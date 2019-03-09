//
//  StatusMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "StatusMode.h"

void testStatusMode()
{
    War *war = new War(make_shared<ProphaseState>());
    for(int i = 0;i < 40; i++)
    {
        war->SetDays(i);
        war->GetState();
    }
    delete war;
}