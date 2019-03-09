//
//  DecoratorMode.h
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__DecoratorMode__
#define __testCPP1__DecoratorMode__

#include <stdio.h>
#include <iostream>
using namespace std;

//装饰模式：动态地给一个对象添加一些额外的职责。就增加功能来说，装饰模式相比生成子类更为灵活。有时我们希望给某个对象而不是整个类添加一些功能。比如有一个手机，允许你为手机添加特性，比如增加挂件、屏幕贴膜等。一种灵活的设计方式是，将手机嵌入到另一对象中，由这个对象完成特性的添加，我们称这个嵌入的对象为装饰。这个装饰与它所装饰的组件接口一致，因此它对使用该组件的客户透明。

//装饰模式 ： 扩展类，不修改父类，可以通过装饰模式为之前的类添加新的方法 接口 属性

//饰模式提供了更加灵活的向对象添加职责的方式。可以用添加和分离的方法，用装饰在运行时刻增加和删除职责。装饰模式提供了一种“即用即付”的方
//法来添加职责。它并不试图在一个复杂的可定制的类中支持所有可预见的特征，相反，你可以定义一个简单的类，并且用装饰类给它逐渐地添加功能。可以从简单的部件组合出复杂的功能。

//外观模式只是统一子系统接口，并不添加属性；建造者模式只是统一创建的方法（Director）；适配模式，老接口不适用，增加一层使得老接口适用
//；代理模式：给真实的对象一个代理对象，也即发言人；组合模式：整体-部分的树形结构，将其它功能组合到另一个功能上

class Phone
{
public:
    Phone(){}
    virtual ~Phone(){}
    virtual void ShowDecorate(){}
};

class iPhone : public Phone
{
private:
    string m_name;
public:
    iPhone(string name) : m_name(name){}
    ~iPhone(){}
    void ShowDecorate(){cout << m_name << "的装饰" << endl;}
};

class NokiaPhone : public Phone
{
private:
    string m_name;
public:
    NokiaPhone(string name) : m_name(name){}
    ~NokiaPhone(){}
    void ShowDecorate(){cout << m_name << "的装饰" << endl;}
};

class DecoratorPhone : public Phone
{
private:
    Phone *m_phone;
public:
    DecoratorPhone(Phone *phone) : m_phone(phone){}
    void ShowDecorate(){m_phone->ShowDecorate();}
};

class DecoratorPhoneA : public DecoratorPhone
{
public:
    DecoratorPhoneA(Phone *phone) : DecoratorPhone(phone){}
    void ShowDecorate()
    {
        DecoratorPhone::ShowDecorate();
        AddDecorate();
    }
private:
    void AddDecorate(){cout << "添加a装饰" << endl;}
};

class DecoratorPhoneB : public DecoratorPhone
{
public:
    DecoratorPhoneB(Phone *phone) : DecoratorPhone(phone){}
    void ShowDecorate()
    {
        DecoratorPhone::ShowDecorate();
        AddDecorate();
    }
private:
    void AddDecorate(){cout << "添加b装饰" << endl;}
};

void testDecorator();


#endif /* defined(__testCPP1__DecoratorMode__) */
