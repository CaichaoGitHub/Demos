//
//  Publish&SubscribeMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "Publish&SubscribeMode.h"

void testObserverMode()
{
    Blog *b = new BlogCSDN("caichao");
    shared_ptr<Observer> o = make_shared<ObserverBlog>("tutupig",b);
    b->Attach(o);
    b->SetStatus("观察者模式");
    b->Notify();
    delete b;
}