//
//  Item_base.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/22.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "Item_base.hpp"
#include <iostream>


void testVirtualProperty()
{
    std::cout << "virtual test" << std::endl;
    
    ItemBase *baseP = new BulkItem();
    
    baseP->netPrice(2);
    
    ItemBase *basePp = new ItemBase();
    
    basePp->netPrice(2);
    
    
    std::cout << "normal test" << std::endl;
    
    baseP->netPriceNormal(2);
    basePp->netPriceNormal(2);
    
    std::cout << "after convert base pointer to child class type" << std::endl;
    
    ((BulkItem*)baseP)->netPriceNormal(2);
    
    delete baseP;
    
    delete basePp;
    
}

void testInheritedProperty()
{
    BulkItem item;
    //item.publicFunction(); // private function , because we declare in private area
    
   // ItemBase2 base2 = item;// private inherit from base ,so convert to private base class is forbidden
    
    BulkItem bulk;
    ItemBase *base = &bulk;
    BulkItem *bp = dynamic_cast<BulkItem*>(base); // directly convert to derived class pointer is forbidden
    
    BulkItem bItem;
    
    //bItem.overloadedFun(); // we can only call the derived version of same named method , because the derived version has coverd the base version
    bItem.overloadedFun(10);
    // if we want to call the base version , we should tell compiler what we want ,like this
    
    // expilicitly specify the base version
    bItem.ItemBase::overloadedFun('a');
    
    // thanks to what we've done before that we tell the compiler we want to using base version of same name method explicitly
    // we can call the base version directly
    bItem.overloadedFun();
    
    base->virtualOverloadedFun("");
    
    
}

void testFriendRelationshipOfBaseclassAndDerivedClass(ItemBase*base)
{
    base->price;
    BulkItem *b = (BulkItem*)base;
    b->discount;
}




