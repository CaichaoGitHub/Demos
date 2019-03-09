//
//  Publish&SubscribeMode.h
//  testCPP1
//
//  Created by caichao on 14-9-28.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__Publish_SubscribeMode__
#define __testCPP1__Publish_SubscribeMode__

#include <stdio.h>
#include <iostream>
#include <list>
#include <memory>
using namespace std;

//观察者模式：定义对象间的一种一对多的依赖关系，当一个对象的状态发生改变时，所有依赖于它的对象都得到通知并被自动更新。它还有两个别名，依赖(Dependents)，发布-订阅(Publish-Subsrcibe)。可以举个博客订阅的例子，当博主发表新文章的时候，即博主状态发生了改变，那些订阅的读者就会收到通知，然后进行相应的动作，比如去看文章，或者收藏起来。博主与读者之间存在种一对多的依赖关系

//将 Observer Object 都进行抽象处理，不同的对象可以更具不同的要求，对Observer进行定制
//observer 使用函数指针 lumbda函数表达式  functional 模板 都可以实现类似观察者的功能

//具体观察者  由于我们要在一个类中调用另一个的函数 我们不适用虚函数而使用function/bind来解决
//class ObserverBlog
//{
//public:
//    typedef boost::function<string ()> UpdateCallBack;
//    
//    ObserverBlog(string name, UpdateCallBack call): m_name(name) , upCall_(call)
//    {}
//    ~ObserverBlog()
//    {}
//    void Update()  //获得更新状态
//    {
//        string status = upCall_();
//        cout<<m_name<<"-------"<<status<<endl;
//    }
//private:
//    string m_name;  //观察者名称
//    UpdateCallBack upCall_;
//};  

//本类参考http://blog.csdn.net/wuzhekai1985/article/details/6674984
//感觉本类设计还有很多的问题，暂时就这样，主要是理解该模式

class Observer
{
public:
    Observer(){}
    virtual ~Observer(){}
    virtual void Update(){}
};

class Blog
{
public:
    Blog(){}
    virtual ~Blog(){}
    void Attach(shared_ptr<Observer> observer)
    {
        m_observers.push_back(observer);
    }
    
    void Remove(shared_ptr<Observer> observer)
    {
        m_observers.remove(observer);
    }
    
    void Notify()
    {
        for(auto itr : m_observers)
        {
            itr->Update();
        }
    }
    
    virtual void SetStatus(string s){m_status = s;}
    virtual string GetStatus(){return m_status;}
    
private:
    list< shared_ptr<Observer> > m_observers;
protected:
    string m_status;
};

class BlogCSDN : public Blog
{
private:
    string m_name;
public:
    BlogCSDN(string name) : m_name(name){}
    ~BlogCSDN(){}
    void SetStatus(string s)
    {
        m_status = "CSDN通知:" + m_name + s;
    }
};

class ObserverBlog : public Observer
{
private:
    string m_name;
    Blog *m_blog;
public:
    ObserverBlog(string name,Blog *blog) : m_name(name), m_blog(blog){}
    ~ObserverBlog(){}
    void Update()
    {
        string status = m_blog->GetStatus();
        cout << m_name << "----" << status << endl;
    }
};

void testObserverMode();


#endif /* defined(__testCPP1__Publish_SubscribeMode__) */
