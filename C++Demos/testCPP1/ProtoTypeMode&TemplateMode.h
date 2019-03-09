//
//  ProtoTypeMode&TemplateMode.h
//  testCPP1
//
//  Created by caichao on 14-9-24.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__ProtoTypeMode_TemplateMode__
#define __testCPP1__ProtoTypeMode_TemplateMode__

#include <stdio.h>
#include <iostream>
using namespace std;

class Resume  //原型模式主要是实现clone接口
{
protected:
    char *name;
public:
    Resume() = default;
    virtual ~Resume() = default;
    virtual Resume* Clone(){return nullptr;}
    virtual void Show(){}
};

class ResumeEx : public Resume
{
public:
    ResumeEx(const char *str)
    {
        if (str == nullptr)
        {
            name = new char[1];
            name[0] = '\0';
        }
        else
        {
            name = new char[strlen(str) + 1];
            strcpy(name, str);
        }
    }
    
    ResumeEx(const ResumeEx &re)
    {
        name = new char[strlen(re.name) + 1];
        strcpy(name, re.name);
    }
    
    virtual ~ResumeEx()
    {
        delete[] name;
    }
    
    Resume *Clone() //实现clone接口,这里有深拷贝（拷贝内存）和浅拷贝（拷贝引用或者指针）之分
    {
        return new ResumeEx(*this);
    }
    
    void Show()
    {
        cout << "ResumeEx name is : " << name << endl;
    }
    
};

void testPrototypeMode();

//模板模式，父类定义基本的操作，子类负责按照接口进行接口编程
class Curriculum //父类定制接口
{
protected:
    virtual void SetPersonalInfo(){}
    virtual void SetEducation(){}
    virtual void SetWorkExp(){}
public:
    void FillResume()
    {
        SetPersonalInfo();
        SetEducation();
        SetWorkExp();
    }
};


class CurriculumCompanyA : public Curriculum
{
    void SetPersonalInfo()
    {
        cout << "coma's personal infomation " << endl;
    }
    void SetEducation()
    {
        cout << "coma's educaton infomation " << endl;
    }
    void SetWorkExp()
    {
        cout << "coma's work experience" << endl;
    }
};

void testTemplateMode();


#endif /* defined(__testCPP1__ProtoTypeMode_TemplateMode__) */
