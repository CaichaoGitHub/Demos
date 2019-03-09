//
//  Memory.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/11/11.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "Memory.hpp"
#include <iostream>
#include <stdlib.h>
#include <memory>

using namespace std;

class NNCls {
    
    
public:
    
    NNCls()
    {
        std::cout << "yes , u construct the object successful " << std::endl;
    }
    
    
};

void testMemory()
{
    NNCls *pN = new NNCls;  // new operator will alloc part of memory from system and init the memory
    
    void *PON = operator new(sizeof(NNCls)); // the operator will only alloc some memory from system
    
    NNCls *pP = new(PON) NNCls; // the operator will only init the PON memory,this technology could help us improve our programs' performance if we use our memory pool , not system
    
    allocator<NNCls> alloc; // the standard allocator
    
    NNCls *pi = alloc.allocate(sizeof(NNCls));
    
    alloc.deallocate(pi, sizeof(NNCls));
    
    alloc.construct(pP); // directly construct one object using placement new
    
    alloc.destroy(pP);
    
    alloc.deallocate(pP,sizeof(NNCls)); // warning error
    
}
