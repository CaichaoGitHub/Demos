//
//  MultiThread.cpp
//  testCPP1
//
//  Created by Caichao on 14/12/23.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "MultiThread.h"
#include <thread>
#include <iostream>
#include <atomic>
#include <ctime>
#include <chrono>
using namespace std;

std::thread::id mainthread_id  =  std::this_thread::get_id();

std::atomic<bool> ready (false);

std::mutex mtx;


void testSleepFor()
{
    cout << "countdonw \n" ;
    for (int i = 10; i > 0; i --)
    {
        std::cout << i << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    cout << "lift off \n";
    return ;
}


//
void testSleepUntil()
{
    using std::chrono::system_clock;
    
    std::time_t tt = system_clock::to_time_t(system_clock::now());
    
    struct std::tm *ptm = std::localtime(&tt);
    
    cout << "current time : " << std::asctime(ptm) << "\n";
    
    cout << "wait 10s \n";
    
//    ptm->tm_min;
    ptm->tm_sec += 10;
    
    std::this_thread::sleep_until(system_clock::from_time_t(mktime(ptm)));
    
    cout << std::asctime(ptm) << " reached\n";
    
    cout << endl;
}

//
void count1m(int id)
{
    while (!ready)
    {
        std::this_thread::yield();
    }
    for (volatile int i = 0; i < 1000000 ; i++) {
        
    }
    mtx.lock();
    cout << "the param id is " << id << endl;
    mtx.unlock();
}

void testYield()
{
    std::thread threads[10];
    cout << "race of 10 threads count to 1 million : \n";
    for (int i = 0 ; i < 10 ; i ++)
    {
        threads[i] = std::thread(count1m,i);
    }
    ready = true;
    for (auto &th : threads)
    {
        th.join();
    }
    
    cout << "\n";
    
    return ;
}
//
void foo()
{
    cout << "foo, threadID is mainThread ? " << (std::this_thread::get_id() == mainthread_id ? "YES" : "NO") << endl;
}

void bar(int x)
{
    cout << "bar:" << x << "  threadID is mainThread ?" << (std::this_thread::get_id() == mainthread_id ? "YES" : "NO") << endl;
}

void testThread()
{
    std::thread first(foo);
    //std::thread second(bar,1);
    
    cout << "foo and bar now execute concurrently" <<endl;
    
    first.join();
    //second.join();
    
    cout << "task completed threadID is mainThread ?  " << (std::this_thread::get_id() == mainthread_id ? "YES" : "NO") << endl;
}

void testSTDMultiThread()
{
    testThread();
    
    testYield();
    
    testSleepUntil();
    
    testSleepFor();
}












