//
//  FacadeMode&CompositeMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-25.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "FacadeMode&CompositeMode.h"

void testCompositeMode()
{
    std::shared_ptr<Company> root = make_shared<ConcreteCompany>("总公司");
    std::shared_ptr<Company> leaf1 = make_shared<FinanceDepartment>("财务部");
    std::shared_ptr<Company> leaf2 = make_shared<HRDepartment>("人力资源部");
    root->Add(leaf1);
    root->Add(leaf2);
    
    std::shared_ptr<Company> mid1 = make_shared<ConcreteCompany>("分公司A");
    std::shared_ptr<Company> leaf3 = make_shared<FinanceDepartment>("财务部");
    std::shared_ptr<Company> leaf4 = make_shared<HRDepartment>("人力资源部");
    mid1->Add(leaf3);
    mid1->Add(leaf4);
    root->Add(mid1);
    
    std::shared_ptr<Company> mid2 = make_shared<ConcreteCompany>("分公司B");
    std::shared_ptr<Company> leaf5 = make_shared<FinanceDepartment>("财务部");
    std::shared_ptr<Company> leaf6 = make_shared<HRDepartment>("人力资源部");
    mid2->Add(leaf5);
    mid2->Add(leaf6);
    root->Add(mid2);
    root->Show(0);
}