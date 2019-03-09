//
//  BuilderMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-25.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "BuilderMode.h"

void testBuilder()
{
    Builder *fb = new FatBuilder;
    Director *di = new Director(fb);
    di->create();
    delete fb;
    delete di;
}