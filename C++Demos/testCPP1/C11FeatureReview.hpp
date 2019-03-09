//
//  C11FeatureReview.hpp
//  testCPP1
//
//  Created by caichao on 15/11/14.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef C11FeatureReview_hpp
#define C11FeatureReview_hpp

#include <stdio.h>
#include <memory>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <cassert>

using namespace std;

// how to make the virtual method work better for us

//override，表示函数应当重写基类中的虚函数。
//final，表示派生类不应当重写这个虚函数。

class BaseCls {
    
    
public:
    
    virtual void testVirtual()const 
    {
        
    }
    
};

class Derived1Cls : public BaseCls {
    
    
public:
    
    void testVirtual()const override
    {
        
    }
    
};

class Derived2Cls : public Derived1Cls {
    
    
public:
    void testVirtual()const final
    {
        
    }
};

class Derived3Cls : public Derived2Cls {
    
    
public:
//    void testVirtual()const
//    {
//        
//    }
};

// 枚举可以指定class
typedef enum class NewEnumCC
{
    Color
}NewEnum;

typedef enum
{
    Color
}OldEnum;

class NewEnumCls {
    
    
public:
    
    NewEnumCls()
    {
        OldEnum mm = Color; // 全局可见
        NewEnum nn = NewEnumCC::Color; // 新枚举，可以指定一个作用域
    }
};

// smart pointer

//unique_ptr: 如果内存资源的所有权不需要共享，就应当使用这个（它没有拷贝构造函数），但是它可以转让给另一个unique_ptr（存在move构造函数）。
//shared_ptr:  如果内存资源需要共享，那么使用这个（所以叫这个名字）。
//weak_ptr: 持有被shared_ptr所管理对象的引用，但是不会改变引用计数值。它被用来打破依赖循环（想象在一个tree结构中，父节点通过一个共享所有权的引用(chared_ptr)引用子节点，同时子节点又必须持有父节点的引用。如果这第二个引用也共享所有权，就会导致一个循环，最终两个节点内存都无法释放）。
//auto_ptr已经被废弃，不会再使用了。

class SmartPointer {
    
    
public:
    
    SmartPointer()
    {
        unique_ptr<int> m(new int(1));
        
        unique_ptr<int> pm = std::move(m);
        
        shared_ptr<int> spm = make_shared<int>(2);
        
        weak_ptr<int> wpm(spm);
    }
    
};

// 非成员begin()和end()

//也许你注意到了，我在前面的例子中已经用到了非成员begin()和end()函数。他们是新加入标准库的，除了能提高了代码一致性，还有助于更多地使用泛型编程。它们和所有的STL容器兼容。更重要的是，他们是可重载的。所以它们可以被扩展到支持任何类型。对C类型数组的重载已经包含在标准库中了。

class BeginEndCls
{
public:
    
    BeginEndCls()
    {
        int arr[3] = {1,2,3};
        //全局 std::begin std::end 支持标准容器算法
        std::for_each(std::begin(arr), std::end(arr), [](int n) {std::cout << n << std::endl;});
    }
    
};

// static_assert和 type traits
class AssertTraits {
    
    
public:
    
    AssertTraits()
    {
        
        
        
        int m = 2;
        std::cout << std::boolalpha;
        std::cout << std::is_integral<int>::value << std::endl;
        //std::remove_const<<#class _Tp#>>
        
        //std::is_integral<m> m;
        
        //mm(m);
    }
    
};


void testFeatureReview();

#endif /* C11FeatureReview_hpp */





