//
//  ChainOfResponsibilityMode.h
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__ChainOfResponsibilityMode__
#define __testCPP1__ChainOfResponsibilityMode__

#include <stdio.h>
#include <iostream>
using namespace std;

//职责链模式：使多个对象都有机会处理请求，从而避免请求的发送者和接收者之间的耦合关系。将这些对象连成一条链，并沿着这条链传递该请求，直到有一个对象处理它为止。其思想很简单，考虑员工要求加薪。公司的管理者一共有三级，总经理、总监、经理，如果一个员工要求加薪，应该向主管的经理申请，如果加薪的数量在经理的职权内，那么经理可以直接批准，否则将申请上交给总监。总监的处理方式也一样，总经理可以处理所有请求。这就是典型的职责链模式，请求的处理形成了一条链，直到有一个对象处理请求。
//if else这样的结构，可以将每个 if else 封装成为一个对象

class Manager
{
protected:
    Manager *m_manager;
    string m_name;
public:
    Manager(Manager *manager, string name):m_manager(manager),m_name(name){}
    virtual void DealWithRequest(string name, int num){}
};

class CommonManager : public Manager
{
public:
    CommonManager(Manager *manager, string name) : Manager(manager,name){}
    void DealWithRequest(string name, int num)
    {
        if (num < 500)
        {
            cout << "经理" << m_name << "批准" << name << "加薪" << num << "元" << endl;
        }
        else
        {
            cout << "经理" << m_name << "无法处理，交由总监处理" << endl;
            m_manager->DealWithRequest(name, num);
        }
            
    }
};

class Majordomo : public Manager
{
public:
    Majordomo(Manager *manager, string name) : Manager(manager,name){}
    void DealWithRequest(string name, int num)
    {
        if (num < 1000)
        {
            cout << "总监" << m_name << "批准" << name << "加薪" << num << "元" << endl;
        }
        else
        {
            cout << "总监" << m_name << "无法处理，交由总经理处理" << endl;
            m_manager->DealWithRequest(name, num);
        }
        
    }
};

class GeneralManager : public Manager
{
public:
    GeneralManager(Manager *manager, string name):Manager(manager,name) {}
    void DealWithRequest(string name, int num)  //总经理可以处理所有请求
    {
        cout << "总经理" << m_name << "批准" << name << "加薪" << num << "元" << endl;
    }
};

void testChainOfResponsibility();

#endif /* defined(__testCPP1__ChainOfResponsibilityMode__) */
