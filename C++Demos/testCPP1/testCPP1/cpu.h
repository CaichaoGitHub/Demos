//
//  cpu.h
//  testCPP1
//
//  Created by caichao on 14-9-19.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__cpu__
#define __testCPP1__cpu__

#include <stdio.h>
#include <iostream>

class AbsSingleCore
{
public:
    virtual void show() = 0;
};

class SingleCoreA : public AbsSingleCore
{
public:
    void show()
    {
        std::cout<<"SingleCoreA"<<std::endl;
    }
};

class SingleCoreB : public AbsSingleCore
{
public:
    void show()
    {
        std::cout<<"SingleCoreB"<<std::endl;
    }
};

//简单工厂
class SingleCoreFactory
{
private:
    SingleCoreFactory(){}
    SingleCoreFactory(const SingleCoreFactory &){}
public:
    
    typedef enum
    {
        CORE_A,
        CORE_B,
    }CORE_TYPE;
    
    static SingleCoreFactory *instance()
    {
        static SingleCoreFactory *instance = NULL;
        if (!instance)
        {
            instance = new SingleCoreFactory;
        }
        return instance;
    }
    AbsSingleCore *createSingleCore (CORE_TYPE type)
    {
        switch (type)
        {
            case CORE_A:
                return new SingleCoreA;
                break;
            case CORE_B:
                return new SingleCoreB;
            default:
                return NULL;
                break;
        }
    }
};

//工厂方法模式
class IFactory
{
public:
    virtual AbsSingleCore* createSingleCore () = 0;
};

class SingleCoreAFactory : public IFactory
{
public:
    AbsSingleCore* createSingleCore ()
    {
        return new SingleCoreA;
    }
    
};

class SingleCoreBFactory : public IFactory
{
public:
    AbsSingleCore* createSingleCore ()
    {
        return new SingleCoreB;
    }
    
};

//抽象工厂模式
class FactoryCreator
{
public:
    static FactoryCreator* instance ()
    {
        static FactoryCreator *instance = NULL;
        if(!instance)
        {
            instance = new FactoryCreator;
        }
        return instance;
    }
    
    IFactory* createSingleCoreAFactory ()
    {
        return new SingleCoreAFactory;
    }
    
    IFactory* createSingleCoreBFactory ()
    {
        return new SingleCoreBFactory;
    }
};

#endif /* defined(__testCPP1__cpu__) */
