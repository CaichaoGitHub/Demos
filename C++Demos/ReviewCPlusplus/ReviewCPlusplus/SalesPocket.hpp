//
//  SalesPocket.hpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/18.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef SalesPocket_hpp
#define SalesPocket_hpp

#include <stdio.h>
#include <vector>
//#include "SalesItem.hpp"

using namespace std;

class SalesItem;

class SalesPocket {
    
    typedef vector<SalesItem> pocketContainer;
    
    pocketContainer items;
    
    //SalesItem p; // only forward declaration,the type is uncompleted , which means the compiler could not calucate precise memory size of the class
    // question: if u make class SalesPocket's method showItemsPrice be a frend member function of SalesItem,so the SalesItem class definition has to include SalesPocket's header file , by change , u want to define a SalesItem member variable in SalesPocket , u have to include SalesItem's header file ; then a problem comes , how to solve the problem that A file include B file and B file include A file at same time ?
    
public:
    
    void showItemsPrice() const;
    
    explicit SalesPocket(pocketContainer::size_type capacity = 1);
    
};

#endif /* SalesPocket_hpp */
