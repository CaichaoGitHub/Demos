//
//  CPPNewFeature.h
//  testCPP1
//
//  Created by Caichao on 14/12/19.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__CPPNewFeature__
#define __testCPP1__CPPNewFeature__

#include <iostream>
#include <memory>
#include <string>
using namespace std;


//test weak_ptr share_ptr  enable_share_from_this

void testCPPNewFeature();

/**
 *  注意：千万不能从一个普通对象(非shared_ptr)使用shared_from_this()获去shared_ptr，例如
 *  self_shared ss;
 *  shared_ptr<self_shared> p = ss.shared_from_this();//错误!
 *  在运行时会导致shared_ptr析构时企图删除一个栈上分配的对象，发生未定义行为。
 */
class TestEnableShareFromThis : public std::enable_shared_from_this<TestEnableShareFromThis>
{
public:
    void testWeakPtr()
    {
        auto sharePtr = std::make_shared<std::string>("china");
        cout << "share origin " << *sharePtr << endl;
        
        auto weakPtr = std::weak_ptr<std::string>(sharePtr);
        
        if (!weakPtr.expired())
        {
            auto sharePtr1 = weakPtr.lock();
            *sharePtr1 = "caichao";
            cout << "share origin " << *sharePtr << endl;
        }
        
    }
    
    void testEnableShareFromThis()
    {
        auto selfSharePtr = shared_from_this();
        selfSharePtr->testWeakPtr();
    }
    
};

#endif /* defined(__testCPP1__CPPNewFeature__) */
