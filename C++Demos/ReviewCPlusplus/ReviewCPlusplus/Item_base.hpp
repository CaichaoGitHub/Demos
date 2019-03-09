//
//  Item_base.hpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/22.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef Item_base_hpp
#define Item_base_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <map>


class ItemBase;

//友员函数或者友员类都是1对1关系，比如一个函数是基类友员，它想访问子类私有参数，必须声明为子类的友员
//友员类的基类如果是某个类的友员，友员的类的子类如果要访问该类的私有成员，必须声明友员类的子类为该类的友员类
//总的来说，友员关系不能继承
void testFriendRelationshipOfBaseclassAndDerivedClass(ItemBase*base);

class ItemBase {
    
    friend void testFriendRelationshipOfBaseclassAndDerivedClass(ItemBase*base);
    
    std::string isbn;
    
protected:
    
    double price;
    
public:
    
    ItemBase()
    {
        price = 1;
        
        netPriceNormal(1); // right now ,the derived class is not be initilized , so the base virtual member function will be called
    }
    
    inline std::string book()const{return isbn;}
    virtual inline double netPrice(std::size_t n)const
    {
        std::cout << "netPrice : base" << std::endl;return 0;
    } // the member function marked by virtual keyword prefers to overloaded by subclass
    
    inline double netPriceNormal(std::size_t n)const
    {
        std::cout << "netPriceNormal : base" << std::endl;return 0;
    }
    
    virtual ~ ItemBase()
    {
        netPriceNormal(2); // the derived class part has been destructed ,so the base version will be invoked
    }
    
    ItemBase(const ItemBase&copyConstructor)
    {}
    
    ItemBase& operator=(const ItemBase& assignOperator)
    {return *this;}
    
    /**
     *  different kinds of overloaded methods
     */
    void overloadedFun()
    {}
    
    void overloadedFun() const
    {}
    
    void overloadedFun(char m)
    {}
    
    virtual void virtualOverloadedFun(const std::string &str)
    {
        std::cout << "base virtual fun" << std::endl;
    }
    
    virtual ItemBase* clone()const  // clone method
    {
        return new ItemBase();
    }
    
    
};

class ItemBase2 {
    
    void privateFunction()
    {
        std::cout << "itembase2 private function" << std::endl;
    }
    
protected:
    void protectedFunction()
    {
        std::cout << "itembase2 protected function" << std::endl;
    }
    
public:
    void publicFunction()
    {
        std::cout << "itembase2 public function" << std::endl;
    }
    
public:
    
};

class ItemBase3 {
    
    
public:
    
    virtual void pureVirtualFun() = 0; // the user can't use the a class which has a unimplemented pure virtual fun
    
};

// refacoring 重构一个类的一种方式是改变继承层次
// 例如在 A - C 的继承中，增加一个类B A - B -C
// 通过访问控制，C只能看到B提供的接口，不能直接访问A的接口，例如构造函数（constructor）
// 是一种重构方式


class BulkItem : public ItemBase,private ItemBase2,public ItemBase3
{
    
//public: // if u feel like the base public should be one of interface of derived class , u should declare it in public area!
    
    using ItemBase2::publicFunction; // u can declare a public function of base class which is inherited by a derived class in privite mode as one of public interface of derived class if u declare it in public;
    
    
    
    std::size_t min_qry;
    double discount;
    
    friend void testFriendRelationshipOfBaseclassAndDerivedClass(ItemBase*base); // while the friend method or class feel like accessing private funs or members  of   derived class , u should declare target method or class in derived class obviously
public:
    
    BulkItem():ItemBase() // call base class constructor,if the base constructor not be called explicitly,the default constructor will be called automatically if it has one
    // declare the constructor as virtual fun is meaningless
    {
        price = 2;
        
        publicFunction();
        
        netPriceNormal(2); // call derived class if it has been implemented,otherwise,the base class version will be invoked
        
    }
    
    BulkItem(const BulkItem& copyContructor):ItemBase(copyContructor){} // call base obviously,the base contrutor will be invoked automatically if u don't call it's copy constructor explicitly
    // so we had better call base copy constructor
    
    ~ BulkItem() // the base destructor will be invoked automatically, however , the reference and the ponter is speacial , if the destructor is virtual fun , the ref or the ptr will call the actual  object,otherwise,what it calls depend on the ref or the ptr type
    
    // in total , we should declare the destructor as virtual function by default
    {
        netPriceNormal(2); // invoke the derived version if it has , otherwise the base version will be invoked automatically
    }
    
    // in addition to the destructor and the constructor , the other base member function will not be invoked automatically , we should call them explicitly  
    
    BulkItem& operator=(const BulkItem&assignOperator) // mark the assign operator as a virtual fun is possiable ,but the action is meaningless since every class has a default opertor = which the param is const self, we can image that the virtual copyContructor is meaningless right ?
    {
        if (this != &assignOperator)
        {
            ItemBase::operator=(assignOperator); // not invoked automatically,we should call it explicitly
        }
        return *this;
    }
    
    double netPrice(std::size_t n)const
    {
        ItemBase::netPrice(n); // if u want call base method , u should call the base version obviously
        
        std::cout << "netPrice : child" << std::endl;return 0;
    } // overloaded virtual func
    
    inline double netPriceNormal(std::size_t n)const
    {
        std::cout << "netPriceNormal : child" << std::endl;return 0;
    }
    
    
    void overloadedFun(int m) // overload the base class same name method ,however the derived version has a int param
    {} // 同名的函数已经覆盖了基类所有的重载版本
    
    // we have to overwrite all of versions of base method if we have overwrite one of them
    // however we can still avoid this happening if we using inner operator "using XXX"
    
    using ItemBase::overloadedFun; // the base version is useful 
    
    void virtualOverloadedFun() // we have defined another version of base version (virtual)
    {
        std::cout << "derived version which has no params , the base version is virtual fun which has a string param" << std::endl;
    }
    
    void pureVirtualFun() // implement the pure virtual fun of base class
    {
        
    }
    
    BulkItem* clone()const  // clone method,it's working that the virtual method  return a different type of pointer or reference in base and derived class if the derived class inherit from the base class
    {
        return new BulkItem();
    }
    
};

//in total , how the c++ compiler determines which member method to call ?
//1.making sure which kind of object call the method ? class object , pointer , reference ?
//2.searching the method through the chain of inheritance,if the compiler can't find the method ,then the operation fails
//3.once the compiler find the method , the compiler will do a lot of test making sure the method is legal
//4.if it's a legal method , the compiler will prouct the executable code,if the method is virtual method , the compiler will call the method dynamicly!


void testVirtualProperty();

void testInheritedProperty();

#endif /* Item_base_hpp */
