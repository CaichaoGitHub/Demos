//
//  MediatorMode.h
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__MediatorMode__
#define __testCPP1__MediatorMode__

#include <stdio.h>
#include <iostream>
using namespace std;

//中介者模式：用一个中介对象来封装一系列的对象交互。中介者使各对象不需要显式地相互引用，从而使其耦合松散，而且可以独立地改变它们之间的交互。中介者模式的例子很多，大到联合国安理会，小到房屋中介，都扮演了中间者的角色，协调各方利益。
//本文就以租房为例子，如果没有房屋中介，那么房客要自己找房东，而房东也要自己找房客，非常不方便。有了房屋中介机构就方便了，房东可以把要出租的房屋信息放到中介机构，而房客可以去中介机构咨询。在软件中，就是多个对象之间需要通信，如果没有中介，对象就需要知道其他对象，最坏情况下，可能需要知道所有其他对象，而有了中介对象就方便多了，对象只需与中介对象通信，而不用知道其他的对象。这就是中介者模式，下面以租房为例

//简化2个对象间的通信机智，对象之间都和中介打交道，无论通信的对象是谁，接口如何，通信方无需知道

class Mediator;
class PPerson
{
protected:
    Mediator *m_mediator;
public:
    virtual void SetMediator(Mediator *mediator){}
    virtual void SendMessage(string message){}
    virtual void GetMessage(string message){}
};

class Mediator
{
public:
    virtual void Send(string message,PPerson *person){}
    virtual void SetA(PPerson *A){}
    virtual void SetB(PPerson *B){}
};

class Renter : public PPerson
{
    friend class HouseMediator;
    void SetMediator(Mediator *mediator){m_mediator = mediator;}
public:
    Renter(){}
    void SendMessage(string message){m_mediator->Send(message, this);}
    void GetMessage(string message){cout << "租房者收到消息:"<<message << endl;}
};

class Lanlord : public PPerson
{
    friend class HouseMediator;
    void SetMediator(Mediator *mediator){m_mediator = mediator;}
public:
    void SendMessage(string message){m_mediator->Send(message, this);}
    void GetMessage(string message){cout << "房东收到消息:"<<message << endl;}
};

class HouseMediator : public Mediator
{
private:
    PPerson *ma;
    PPerson *mb;
public:
    HouseMediator() : ma(0),mb(0){}
    void Send(string message,PPerson *person)
    {
        if(person == ma)
        {
            mb->GetMessage(message);
        }
        else
        {
            ma->GetMessage(message);
        }
    }
    void SetA(PPerson *A){ma = A;ma->SetMediator(this);}
    void SetB(PPerson *B){mb = B;mb->SetMediator(this);}
};

void testMediatorMode();





#endif /* defined(__testCPP1__MediatorMode__) */
