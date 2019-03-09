//
//  ProtoTypeMode&TemplateMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-24.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "ProtoTypeMode&TemplateMode.h"

void testPrototypeMode()
{
    Resume *r1 , *r2 ,*r3 , *r4;
    r1 = new ResumeEx("abc");
    r2 = new ResumeEx("123");
    r3 = r1->Clone();
    r4 = r2->Clone();
    r1->Show();
    r2->Show();
    delete r1;
    delete r2;
    r3->Show();
    r4->Show();
    delete r3;
    delete r4;
}

void testTemplateMode()
{
    Curriculum *r1;
    r1 = new CurriculumCompanyA;
    r1->FillResume();
    delete r1;
}