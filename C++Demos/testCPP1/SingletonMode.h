//
//  SingletonMode.h
//  testCPP1
//
//  Created by caichao on 14-9-24.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__SingletonMode__
#define __testCPP1__SingletonMode__

#include <stdio.h>


#include <iostream>
using namespace std;

class Singleton
{
public:
    virtual void show() = 0;
};

class SingletonA : public Singleton
{
public:
    void show()
    {
        cout<<"SingletonA" <<endl;
    }
};

class SingletonB : public Singleton
{
public:
    void show()
    {
        cout<< "SingletonB" <<endl;
    }
};

//使用简单工厂模式 + 单例模式
class SingletonFactory
{
private: //需要将这些功能设置为私有，或者设置为 delete, 默认构造函数 析构函数不要设置为 delete
    SingletonFactory() = default;
    SingletonFactory(const SingletonFactory &) = delete;
    ~SingletonFactory() = default;
    SingletonFactory& operator = (const SingletonFactory &) = delete;
public:
    typedef enum
    {
        SA,
        SB,
    }StrategyType;
public:
    static SingletonFactory& Instance() //最好返回引用，这样外部是无法删除该对象的，防止外部接口的误操作
    {
        static SingletonFactory* instance = NULL;
        if (!instance)
        {
            static std::mutex mLock;   //单例模式一般需要加锁，可以使用双重锁技术优化代码效率
            mLock.lock();
            if(!instance)
            {
                instance = new SingletonFactory;
            }
            mLock.unlock();
        }
        return *instance;
    }
    
    Singleton *CreateSingletonFactory(StrategyType type)
    {
        switch (type)
        {
            case SA:
                return new SingletonB;
                break;
            case SB:
                return new SingletonA;
                break;
            default:
                break;
        }
    }
};

#endif /* defined(__testCPP1__SingletonMode__) */
