//
//  main.cpp
//  testCPP1
//
//  Created by caichao on 14-9-19.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include <iostream>
#include "cpu.h"
#include "Cache.h"
#include "C11NewFeature.h"
#include "AdapterMode.h"
#include "ProtoTypeMode&TemplateMode.h"
#include "BuilderMode.h"
#include "FacadeMode&CompositeMode.h"
#include "ProxyMode.h"
#include "FlyweightMode.h"
#include "BridgeMode.h"
#include "DecoratorMode.h"
#include "MementoMode.h"
#include "MediatorMode.h"
#include "ChainOfResponsibilityMode.h"
#include "Publish&SubscribeMode.h"
#include "StatusMode.h"
#include "CPPNewFeature.h"
#include "MultiThread.h"
#include "C11FeatureReview.hpp"

//#define EXCEPTONS_TEST

using namespace std;

void oldtest()
{
    AbsSingleCore *core = SingleCoreFactory::instance()->createSingleCore(SingleCoreFactory::CORE_A);
    core->show();
    delete core;
    core = SingleCoreFactory::instance()->createSingleCore(SingleCoreFactory::CORE_B);
    core->show();
    delete core;
    
#ifdef EXCEPTONS_TEST
    //Cache类中的析构函数不实现delete操作，而让用户自己释放才是普遍的行为，而且这也是在当类有很多其他操作是的做法。
    ReplaceAlgorithm *pra = NULL;
    LRU_ReplaceAlgorithm LRUR;
    pra = &LRUR;
    Cache cacheCrash(pra);
    cacheCrash.Replace();
#endif
    
    Cache cache(new LRU_ReplaceAlgorithm);
    cache.Replace();
    
    Cache *cf = CacheFactory::Instance()->CreateCache(CacheFactory::FIFO);
    cf->Replace();
    delete cf;
    
    CacheTemplate<Random_ReplaceAlgorithm> ct;
    ct.Replace();
    
    testNewFeature();
    
    Sequence *s1 = new Stack;
    Sequence *s2 = new Queue;
    s1->push(1);
    s1->push(2);
    s2->pop();
    s2->pop();
    delete s1;
    delete s2;
    
    testPrototypeMode();
    
    testTemplateMode();
    
    testBuilder();
    
    testCompositeMode();
    
    testProxyMode();
    
    testFlyweightMode();
    
    testBridge();
    
    testDecorator();
    
    testMementoMode();
    
    testMediatorMode();
    
    testChainOfResponsibility();
    
    testObserverMode();
    
    testStatusMode();
    
    testCPPNewFeature();
    
    testSTDMultiThread();
}

int main(int argc, const char * argv[])
{
    
    testFeatureReview();
    
}


