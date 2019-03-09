//
//  ProxyMode.h
//  testCPP1
//
//  Created by caichao on 14-9-26.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__ProxyMode__
#define __testCPP1__ProxyMode__

#include <stdio.h>
#include <iostream>
using namespace std;

//[DP]上的定义：为其他对象提供一种代理以控制对这个对象的访问。有四种常用的情况：
//（1）远程代理（为一个对象在不同的地址空间提供局部代表），
//（2）虚代理(普通代理，创建大的开销的对象，可以通过代理来进行对象创建的控制)，
//（3）保护代理（控制真是对象的访问时的权限），
//（4）智能引用(智能指针,当我们操作指针的时候，其实只需要去操作引用对象就可以了，不需要去操作实际的指针)。

//本文主要介绍虚代理和智能引用两种情况。
//考虑一个可以在文档中嵌入图形对象的文档编辑器。有些图形对象的创建开销很大。但是打开文档必须很迅速，因此我们在打开文档时应避免一次性创建所有开销很大的对象。这里就可以运用代理模式，在打开文档时，并不打开图形对象，而是打开图形对象的代理以替代真实的图形。待到真正需要打开图形时，仍由代理负责打开。这是[DP]一书上的给的例子。下面给出代理模式的UML图。
class CImage
{
public:
    CImage(string name) : m_name(name){}
    virtual ~CImage(){}
    virtual void Show(){}
protected:
    string m_name;
};

class BCImage : public CImage
{
public:
    BCImage(string name) : CImage(name){}
    ~BCImage(){}
    void Show(){cout << "Show big image " << endl;}
};

class BCImageProxy //这里一种实现方式是 BCImageProxy ： CImage 继承的方式,另一种则是现在采用的这种方式，以组合的方式
{
public:
    BCImageProxy(string name)
    {
        pBCImage = new BCImage(name);
    }
    virtual ~BCImageProxy()
    {
        delete pBCImage;
    }
    void Show()
    {
        pBCImage->Show();
    }
private:
    BCImage *pBCImage;
};

void testProxyMode();

#endif /* defined(__testCPP1__ProxyMode__) */
