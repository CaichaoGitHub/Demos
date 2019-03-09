//
//  FlyweightMode.h
//  testCPP1
//
//  Created by caichao on 14-9-26.
//  Copyright (c) 2014年 caichao. All rights reserved.
//

#ifndef __testCPP1__FlyweightMode__
#define __testCPP1__FlyweightMode__

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

//用享元模式。其定义为：运用共享技术有效地支持大量细粒度的对象。将一些共有的属性放到一起，其它的有区别的属性进行单独的存储就可以了
typedef enum : short
{
    BLACK,
    WHITE
} PieceColor;

class PiecePos
{
public:
    unsigned x;
    unsigned y;
    PiecePos() : x(0) , y(0) {}
    PiecePos(unsigned a,unsigned b) : x(a) , y(b){}
    PiecePos(const PiecePos &pp) = default;
    PiecePos& operator = (const PiecePos& pp) = default;
};

class PieceAttribute //棋子属性
{
public:
    PiecePos pos;
    PieceColor color;
    PieceAttribute() {};
    PieceAttribute(const PieceAttribute&) = default;
    PieceAttribute& operator = (const PieceAttribute&) = default;
};

class Piece
{
public:
    virtual void Draw(const PieceAttribute &pa)
    {
        if (pa.color == PieceColor::BLACK)
        {
            cout << "绘制一颗白色的棋子" ;
        }
        else if (pa.color == PieceColor::BLACK)
        {
            cout << "绘制一颗黑色的棋子" ;
        }
        cout << "在坐标(" << pa.pos.x << "," << pa.pos.y << ")" << endl;
    }
};

class PieceBoard
{
private:
    vector<PieceAttribute> m_vecPAttributes;
    Piece m_piece;
    string m_bName;
    string m_wName;
public:
    PieceBoard(string b, string w) : m_bName(b), m_wName(w)
    {
        cout << b << "和" << w << "的对战开始" << endl;
    }
    ~PieceBoard(){}
    void setPiece(const PieceAttribute &pa)
    {
        m_vecPAttributes.push_back(pa);
        m_piece.Draw(pa);
    }
};

void testFlyweightMode();

#endif /* defined(__testCPP1__FlyweightMode__) */
