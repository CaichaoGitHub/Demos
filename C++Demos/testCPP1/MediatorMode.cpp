//
//  MediatorMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "MediatorMode.h"

void testMediatorMode()
{
    Mediator *med = new HouseMediator;
    PPerson *p1 = new Renter;
    PPerson *p2 = new Lanlord;
    med->SetA(p1);
    med->SetB(p2);
    //p1->SetMediator(med);
    //p2->SetMediator(med);
    p1->SendMessage("我想租房子");
    p2->SendMessage("我有房子出租");
    delete p1;
    delete p2;
    delete med;
}