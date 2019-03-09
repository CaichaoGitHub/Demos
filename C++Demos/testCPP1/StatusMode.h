//
//  StatusMode.h
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__StatusMode__
#define __testCPP1__StatusMode__

#include <stdio.h>
#include <iostream>
#include <memory>
using namespace std;

// 状态模式：允许一个对象在其内部状态改变时改变它的行为。对象看起来似乎修改了它的类。它有两种使用情况：
//（1）一个对象的行为取决于它的状态, 并且它必须在运行时刻根据状态改变它的行为。
//（2）一个操作中含有庞大的多分支的条件语句，且这些分支依赖于该对象的状态。
//本文的例子为第一种情况，以战争为例，假设一场战争需经历四个阶段：前期、中期、后期、结束。当战争处于不同的阶段，战争的行为是不一样的，也就说战争的行为取决于所处的阶段，而且随着时间的推进是动态变化的。

//本文参考http://blog.csdn.net/wuzhekai1985/article/details/6675799 这里只做该模式的设计与理解

class War;
class State
{
public:
    virtual void Prophase(){}
    virtual void Metaphase(){}
    virtual void Anaphase(){}
    virtual void End(){}
    virtual void CurrentState(War *war){}
};

class War
{
private:
    shared_ptr<State> m_state;
    int m_days;
public:
    War(shared_ptr<State> state) : m_state(state), m_days(0){}
    ~War(){}
    int GetDays(){return m_days;}
    void SetDays(int days){m_days = days;}
    void SetState(shared_ptr<State> state){m_state = state;}
    void GetState(){m_state->CurrentState(this);}
};

class EndState : public State
{
public:
    void End(War *war)
    {
        cout << "战争结束" << endl;
    }
    void CurrentState(War *war){End(war);}
};

class AnaphaseState : public State
{
public:
    void Anaphase(War *war)
    {
        if (war->GetDays() < 30)
        {
            cout << "第" << war->GetDays() << "天：战争后期，双方拼死一搏" << endl;
        }
        else
        {
            war->SetState(make_shared<EndState>());
            war->GetState();
        }
    }
    
    void CurrentState(War *war){Anaphase(war);};
    
};

class MetaphaseState : public State
{
public:
    void Metaphase(War *war)
    {
        if (war->GetDays() < 20)
        {
            cout << "第" << war->GetDays() << "天：战争中期，进入相持阶段，双发各有损耗" << endl;
        }
        else
        {
            war->SetState(make_shared<AnaphaseState>());
            war->GetState();
        }
    }
    void CurrentState(War *war){Metaphase(war);}
};

class ProphaseState : public State
{
public:
    void Prophase(War *war)
    {
        if (war->GetDays() < 10)
        {
            cout << "第" << war->GetDays() << "天：战争初期，双方你来我往，互相试探对方" << endl;
        }
        else
        {
            war->SetState(make_shared<MetaphaseState>());
            war->GetState();
        }
    }
    void CurrentState(War *war){Prophase(war);}
};

void testStatusMode();

#endif /* defined(__testCPP1__StatusMode__) */
