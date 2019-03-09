//
//  BuilderMode.h
//  testCPP1
//
//  Created by caichao on 14-9-25.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__BuilderMode__
#define __testCPP1__BuilderMode__

#include <stdio.h>
#include <iostream>
using namespace std;

class Builder //建造模式的特点就是具体的建造功能由一个Director去管理
//这其实就很像游戏里面的那套绘图逻辑，通过Director来控制整个游戏的逻辑
{
public:
    virtual void BuildHead(){}
    virtual void BuildBody(){}
    virtual void BuildLeftArm(){}
    virtual void BuildRightArm(){}
    virtual void BuildLeftLeg(){}
    virtual void BuildRightLeg(){}
};

class FatBuilder : public Builder
{
public:
    void BuildHead(){ cout << "fat head" << endl;}
    void BuildBody(){ cout << "fat body " << endl; }
    void BuildLeftArm(){ cout << "fat left arm" << endl;}
    void BuildRightArm(){ cout << "fat right arm" << endl;}
    void BuildLeftLeg(){ cout << "fat left leg" << endl;}
    void BuildRightLeg(){ cout << "fat right leg " <<endl;}
};

class ThinBuilder : public Builder
{
    void BuildHead(){ cout << "thin head" << endl;}
    void BuildBody(){ cout << "thin body " << endl; }
    void BuildLeftArm(){ cout << "thin left arm" << endl;}
    void BuildRightArm(){ cout << "thin right arm" << endl;}
    void BuildLeftLeg(){ cout << "thin left leg" << endl;}
    void BuildRightLeg(){ cout << "thin right leg " <<endl;}
};

class Director //建造者模式中最重要的导演
{
private:
    Builder *m_pBuilder;
public:
    Director(Builder *builer) : m_pBuilder(builer){}
    void create()
    {
        m_pBuilder->BuildHead();
        m_pBuilder->BuildBody();
        m_pBuilder->BuildLeftArm();
        m_pBuilder->BuildRightArm();
        m_pBuilder->BuildLeftLeg();
        m_pBuilder->BuildRightLeg();
    }
};

void testBuilder();

#endif /* defined(__testCPP1__BuilderMode__) */
