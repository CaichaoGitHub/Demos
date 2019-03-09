//
//  BridgeMode.h
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__BridgeMode__
#define __testCPP1__BridgeMode__

#include <stdio.h>
#include <iostream>
using namespace std;

// [DP]书上定义：将抽象部分与它的实现部分分离，使它们都可以独立地变化。考虑装操作系统，有多种配置的计算机，同样也有多款操作系统。如何运用桥接模式呢？可以将操作系统和计算机分别抽象出来，让它们各自发展，减少它们的耦合度。当然了，两者之间有标准的接口。这样设计，不论是对于计算机，还是操作系统都是非常有利的。

class OS
{
public:
    virtual void InstallOS_Imp() = 0;
};

class WindowOS : public OS
{
public:
    void InstallOS_Imp()
    {
        cout << "安装windows " << endl;
    }
};

class LiunxOS : public OS
{
public:
    void InstallOS_Imp()
    {
        cout << "安装Liunx " << endl;
    }
};

class UnixOS : public OS
{
public:
    void InstallOS_Imp()
    {
        cout << "安装Unix " << endl;
    }
};

class Computer
{
public:
    virtual void InstallOS(OS *os) = 0;
};

class AppleComputer : public Computer
{
public:
    void InstallOS(OS *os)
    {
        os->InstallOS_Imp();
    }
};

class HPComputer : public Computer
{
public:
    void InstallOS(OS *os)
    {
        os->InstallOS_Imp();
    }
};

void testBridge();

#endif /* defined(__testCPP1__BridgeMode__) */
