//
//  Cache.h
//  testCPP1
//
//  Created by caichao on 14-9-23.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__Cache__
#define __testCPP1__Cache__

#include <stdio.h>
#include <iostream>
using namespace std;

class ReplaceAlgorithm
{
public:
    virtual void Replace() = 0;
};

class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace()
    {
        cout<<"Least Recently Used replace algorithm" <<endl;
    }
};

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace()
    {
        cout<< "First in First out replace algorithm" <<endl;
    }
};

class Random_ReplaceAlgorithm : public ReplaceAlgorithm
{
public:
    void Replace()
    {
        cout<< "random replace algorithm" <<endl;
    }
};

//直接使用，知道具体的算法
class Cache
{
private:
    ReplaceAlgorithm *m_ra;
public:
    Cache(ReplaceAlgorithm *ra):m_ra(ra){}
    virtual ~Cache()
    {
        delete m_ra;
    }
    void Replace()
    {
        m_ra->Replace();
    }
};

//使用简单工厂模式
class CacheFactory
{
public:
    typedef enum
    {
        LRU,
        FIFO,
        RANDOM,
    }StrategyType;
public:
    static CacheFactory* Instance()
    {
        static CacheFactory* instance = NULL;
        if (!instance)
        {
            instance = new CacheFactory;
        }
        return instance;
    }
    
    Cache *CreateCache(StrategyType type)
    {
        switch (type)
        {
            case LRU:
                return new Cache(new LRU_ReplaceAlgorithm());
                break;
            case FIFO:
                return new Cache(new FIFO_ReplaceAlgorithm());
                break;
            case RANDOM:
                return new Cache(new Random_ReplaceAlgorithm());
                break;
            default:
                break;
        }
    }
};

//使用模板
template <class RA>
class CacheTemplate {
    RA m_ra;
public:
    CacheTemplate(){}
    ~CacheTemplate(){}
    void Replace()
    {
        m_ra.Replace();
    }
};

#endif /* defined(__testCPP1__Cache__) */
