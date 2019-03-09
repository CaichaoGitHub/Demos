//
//  MementoMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "MementoMode.h"

void testMementoMode()
{
    Caretake caretake;
    GameRole role;
    role.Show();
    caretake.Save(role.Save());
    role.Attack();
    role.Show();
    role.Load(caretake.Load(0));
    role.Show();
    
}