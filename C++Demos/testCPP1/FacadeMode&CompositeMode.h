//
//  FacadeMode&CompositeMode.h
//  testCPP1
//
//  Created by caichao on 14-9-25.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__FacadeMode_CompositeMode__
#define __testCPP1__FacadeMode_CompositeMode__

#include <stdio.h>
#include <memory>
#include <list>
#include <iostream>
using namespace std;

//外观模式，其实和很多模式很相似，比如组合，建造者等，它将多个子功能合成为一个大的功能给
//外部使用

//这就是外观模式，它有几个特点（摘自DP一书），（1）它对客户屏蔽子系统组件，因而减少了客户处理的对象的数目并使得子系统使用起来更加方便。（2）它实现了子系统与客户之间的松耦合关系，而子系统内部的功能组件往往是紧耦合的。（3）如果应用需要，它并不限制它们使用子系统类。
//结合上面编译器这个例子，进一步说明。对于（1），编译器类对客户屏蔽了子系统组件，客户只需处理编译器的对象就可以方便的使用子系统。对于（2），子系统的变化，不会影响到客户的使用，体现了子系统与客户的松耦合关系。对于（3），如果客户希望使用词法分析器，只需定义词法分析的类对象即可，并不受到限制。

class Scanner
{
public:
    void Scan(){cout << "词法分析" << endl;}
};

class Parser
{
public:
    void Parse(){cout << "语法分析"  << endl;}
};

class GenMidCode
{
public:
    void GenCode(){cout << "产生中间代码" << endl;}
};

class GenMachineCode
{
public:
    void GenCode(){cout << "产生机器代码" << endl;}
};

class Compiler
{
public:
    void Run()
    {
        Scanner scanner; //并不是compiler的成员变量~~
        Parser parser;
        GenMidCode genMidCode;
        GenMachineCode genMacCode;
        scanner.Scan();
        parser.Parse();
        genMidCode.GenCode();
        genMacCode.GenCode();
    }
};

//DP书上给出的定义：将对象组合成树形结构以表示“部分-整体”的层次结构。组合使得用户对单个对象和组合对象的使用具有一致性。注意两个字“树形”。这种树形结构在现实生活中随处可见，比如一个集团公司，它有一个母公司，下设很多家子公司。不管是母公司还是子公司，都有各自直属的财务部、人力资源部、销售部等。对于母公司来说，不论是子公司，还是直属的财务部、人力资源部，都是它的部门。整个公司的部门拓扑图就是一个树形结构。


class Company
{
public:
    Company(string name) : m_name(name){}
    virtual ~Company(){}
    virtual void Add(std::shared_ptr<Company> pC){}
    virtual void Show(int depth){}
protected:
    string m_name;
};

class FinanceDepartment : public Company
{
public:
    FinanceDepartment(string name) : Company(name){}
    virtual ~FinanceDepartment(){}
    virtual void Show(int depth)
    {
        for (int i = 0;i < depth ;i ++)
        {
            cout << "-";
        }
        cout << m_name << endl;
    }
};

class HRDepartment : public Company
{
public:
    HRDepartment(string name) : Company(name){}
    virtual ~HRDepartment(){}
    virtual void Show(int depth)
    {
        for (int i = 0;i < depth ;i ++)
        {
            cout << "-";
        }
        cout << m_name << endl;
    }
};

class ConcreteCompany : public Company
{
public:
    ConcreteCompany(string name) : Company(name){}
    virtual ~ConcreteCompany(){}
    void Add(std::shared_ptr<Company> pC)
    {
        m_listCompany.push_back(pC);
    }
    void Show(int depth)
    {
        for (int i = 0;i < depth ;i ++)
        {
            cout << "-";
        }
        cout << m_name << endl;
        for(auto itr : m_listCompany)
        {
            itr->Show(depth + 2);
        }
    }
private:
    list< std::shared_ptr<Company> > m_listCompany; //对象的生命周期还是谁创建，谁管理的方式
};


void testCompositeMode();



#endif /* defined(__testCPP1__FacadeMode_CompositeMode__) */
