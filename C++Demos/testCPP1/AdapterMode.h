//
//  AdapterMode.h
//  testCPP1
//
//  Created by caichao on 14-9-24.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__AdapterMode__
#define __testCPP1__AdapterMode__

#include <stdio.h>
#include <iostream>
using namespace std;

//使用双端队列实现队列和栈
class Deque
{
public:
    void push_back(int x)
    {
        cout << "Deque push back " << endl;
    }
    
    void push_front(int x)
    {
        cout << "Deque push front " << endl;
    }
    
    void pop_back()
    {
        cout << "Deque pop back" << endl;
    }
    
    void pop_front()
    {
        cout << "Deque pop front" << endl;
    }
};

class Sequence
{
public:
    virtual void push(int x) = 0;
    virtual void pop() = 0;
};

class Stack : public Sequence
{
public:
    void push(int x)
    {
        deque.push_back(x);
    }
    
    void pop()
    {
        deque.pop_back();
    }
    
private:
    Deque deque;
};

class Queue : public Sequence
{
public:
    void push(int x)
    {
        deque.push_back(x);
    }
    
    void pop()
    {
        deque.pop_front();
    }
private:
    Deque deque;
};





#endif /* defined(__testCPP1__AdapterMode__) */
