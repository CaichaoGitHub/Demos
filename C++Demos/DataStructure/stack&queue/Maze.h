//
// Created by caichao on 2019-03-22.
//

#ifndef DATASTRUCTURE_MAZE_H
#define DATASTRUCTURE_MAZE_H
#include "ArrayStack.h"
#include <iostream>
#include <stack>

#define kMSize 20

class Maze
{
public:

    static void Test()
    {
        Maze maze;
        maze.LogMaa();
        maze.Walk();
        maze.LogMaa();
    }

    Maze(){

        InitMaa();
    }

    void Walk()
    {
        auto pass = [this](int x ,int y)->bool{

            if (x < kMSize && y < kMSize)
            {
                return this->maa[x][y] > 0 && this->maa[x][y] < 3;
            }
            return false;

        };

        auto isEnd = [this](int x ,int y)->bool{

            return this->maa[x][y] == 2;

        };

        auto markNoAccessiable = [this](int x, int y) -> bool{
            this->maa[x][y] = 3;
        };

        auto goNext = [this](Elem &e) -> void{

            switch (e.dir)
            {
                case 0:
                {
                    e.xp ++;
                }
                    break;
                case 1:
                {
                    e.yp ++;
                }
                    break;
                case 2:
                {
                    e.xp ++;
                    e.yp ++;
                }
                    break;
            }
            e.dir = 0;
        };

        Elem cur = {0,0,0};

        do{

            if (pass(cur.xp,cur.yp))
            {
                stack.push(cur);
                if (isEnd(cur.xp,cur.yp))
                {
                    while (!stack.empty())
                    {
                        cur = stack.top();
                        stack.pop();
                        this->maa[cur.xp][cur.yp] = 4;
                    }

                    break;
                }
                goNext(cur);
            }
            else
            {
                if (!stack.empty())
                {
                    cur = stack.top();
                    stack.pop();
                    while (cur.dir == 2 && !stack.empty())
                    {
                        markNoAccessiable(cur.xp,cur.yp);
                        cur = stack.top();
                        stack.pop();
                    }
                    if (cur.dir < 2)
                    {
                        cur.dir ++;
                        stack.push(cur);
                        goNext(cur);
                    }
                }
            }

        }while (!stack.empty());
    }

    void InitMaa()
    {
        for (int i = 0; i < kMSize; ++i)
        {
            maa[i][i] = 1;
            if (i > 0)
            {
                maa[i][i-1] = 1;
            }

            if (i == kMSize - 1)
            {
                maa[i][i] = 1;
            }
        }

        for (int j = 0; j < kMSize; ++j)
        {
            maa[5][j] = 1;
            maa[7][j] = 1;
            maa[j][3] = 1;
            maa[j][6] = 1;
        }

        maa[10][6] = 2;
    }

    void LogMaa()
    {
        std::cout << std::endl;
        for (int i = 0; i < kMSize; ++i)
        {
            for (int j = 0; j < kMSize; ++j)
            {
                std::cout << maa[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }


private:
    struct Elem{

        int xp;
        int yp;

        int dir;

    };

    int maa[kMSize][kMSize] = {0};
    std::stack<Elem> stack;

};

#endif //DATASTRUCTURE_MAZE_H
