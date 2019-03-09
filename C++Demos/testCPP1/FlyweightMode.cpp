//
//  FlyweightMode.cpp
//  testCPP1
//
//  Created by caichao on 14-9-26.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#include "FlyweightMode.h"

void testFlyweightMode()
{
    PieceBoard pb("caichao","chaocai");
    PieceAttribute pa1;
    pa1.pos = PiecePos(10, 20);
    pa1.color = PieceColor::BLACK;
    pb.setPiece(pa1);
}