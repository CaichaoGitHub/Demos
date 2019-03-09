//
//  SalesPocket.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/18.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "SalesPocket.hpp"
#include "SalesItem.hpp"
#include <iostream>


SalesPocket::SalesPocket(pocketContainer::size_type capacity)
{
    items.reserve(capacity);
    
    SalesItem item;
    
//    item.revenue;
    
    items.push_back(item);
}

void SalesPocket::showItemsPrice() const
{
    pocketContainer::const_iterator iterator = items.begin();
    for (;iterator != items.end();iterator++)
    {
        cout << iterator->revenue << "\t";
    }
    cout << endl;
}