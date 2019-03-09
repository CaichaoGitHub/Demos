//
//  Namespace.cpp
//  ReviewCPlusplus
//
//  Created by caichao on 15/11/11.
//  Copyright © 2015年 caichao. All rights reserved.
//

#include "Namespace.hpp"
#include <string>
#include <iostream>

namespace abc {
    class cl
    {
    public:
        friend void ff();
    };
}

namespace test
{
    int m;
    namespace
    {
        int m;
    }
    
    namespace nn
    {
        int m;
    }
}

void testd()
{
    std::string mstr;
    
    //cout << mstr << endl;
    
    abc::cl m;
    
    //ff();
    
}
