//
//  SmartPonter.hpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/10/20.
//  Copyright © 2015年 caichao. All rights reserved.
//

#ifndef SmartPonter_hpp
#define SmartPonter_hpp

#include <stdio.h>

class HasPtr;

class U_Ptr { // the class of saving pointer and pointer counter
    
    friend class HasPtr;
    
    int *ip;
    size_t use;
    
    U_Ptr(int *p):ip(p),use(1){}
    ~ U_Ptr()
    {
        delete ip;
    }
    
};


class HasPtr
{
public:
    
    HasPtr(int *p , int i):ptr(new U_Ptr(p)),val(i){}
    HasPtr(const HasPtr &ori)
    {
        
    }
    
    HasPtr& operator = (const HasPtr& ori)
    {
        ++ ori.ptr->use;
        if (--ptr->use)
        {
            delete ptr;
        }
        ptr = ori.ptr;
        val = ori.val;
        return *this;
    }
    
    ~ HasPtr()
    {
        delete ptr;
    }
    
private:
    
    U_Ptr *ptr;
    int val;
    
};


#endif /* SmartPonter_hpp */
