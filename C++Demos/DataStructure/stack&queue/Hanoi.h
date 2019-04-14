//
// Created by caichao on 2019-03-23.
//

#ifndef DATASTRUCTURE_HANOI_H
#define DATASTRUCTURE_HANOI_H
#include <stdio.h>

class Hanoi
{
public:
    void hanoi(int n, char A, char B , char C)
    {
        if (n == 1)
            move(A,C);
        else
        {
            hanoi(n-1,A,C,B);
            move(A,C);
            hanoi(n-1,B,A,C);
        }
    }

    void move(char A, char C)
    {
        printf("move %c - > %c \n",A,C);
        fflush(stdout);
    }

    static void Test()
    {
        Hanoi hanoi1;
        hanoi1.hanoi(2,'A','B','C');
    }
};

#endif //DATASTRUCTURE_HANOI_H
