//
//  MementoMode.h
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__MementoMode__
#define __testCPP1__MementoMode__

#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

//备忘录模式：在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可将该对象恢复到原先保存的状态[DP]。举个简单的例子，我们玩游戏时都会保存进度，所保存的进度以文件的形式存在。这样下次就可以继续玩，而不用从头开始。这里的进度其实就是游戏的内部状态，而这里的文件相当于是在游戏之外保存状态。这样，下次就可以从文件中读入保存的进度，从而恢复到原来的状态。这就是备忘录模式。

class Memento
{
public:
    int m_vitality ;
    int m_attack;
    int m_defense;
public:
    Memento(int vitality ,int attack, int defense):
    m_vitality(vitality),m_attack(attack),m_defense(defense){}
    
    Memento& operator = (const Memento &memto)
    {
        m_vitality = memto.m_vitality;
        m_attack = memto.m_attack;
        m_defense = memto.m_defense;
        return *this;
    }
};

class GameRole
{
private:
    int m_vitality ;
    int m_attack;
    int m_defense;
public:
    GameRole() : m_vitality(100),m_attack(100),m_defense(100){}
    
    Memento Save()
    {
        Memento memto(m_vitality,m_attack,m_defense);
        return memto;
    }
    
    void Load(Memento memto)
    {
        m_vitality = memto.m_vitality;
        m_attack = memto.m_attack;
        m_defense = memto.m_defense;
    }
    
    void Show(){cout << "vitality : " << m_vitality << ", attact : " << m_attack << ", defense : " << m_defense << endl;}
    
    void Attack(){m_vitality -= 10; m_defense -= 10; m_attack -= 10;}
};

class Caretake
{
public:
    void Save(Memento memto){ m_vecMemento.push_back(memto); }
    Memento Load(int state) { return m_vecMemento[state]; }
private:
    vector<Memento> m_vecMemento;
};

void testMementoMode();



#endif /* defined(__testCPP1__MementoMode__) */
