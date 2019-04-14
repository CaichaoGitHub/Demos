//
// Created by caichao on 2019-04-05.
//

#ifndef DATASTRUCTURE_STATICSEARCHTREE_H
#define DATASTRUCTURE_STATICSEARCHTREE_H

#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <cmath>

class StaticSearchTree
{
public:

    struct TNode{
        char data;
        TNode *lchild = nullptr;
        TNode *rchild = nullptr;
    };

    static const int _maxSize = 20;

    TNode *root = nullptr;


public:

    static void Test()
    {
        StaticSearchTree tree;
    }

    StaticSearchTree()
    {
        char R[10] = {'A','B','C','D','E','F','G','H','I'};
        float sw[10] = {1,2,4,9,12,16,20,23,28};
        CreateSecondOptimal(root,R,sw,0,8);
    }

    /**
     * \param T , search tree to construct
     * \param R , search data,
     * \param sw, search sum weight
     * \param low, low index
     * \param high, high index
     * */
    void CreateSecondOptimal(TNode *&T,char R[],float sw[],int low,int high) //nearly optimal search tree
    {
        int i = low;
        float min = fabs(sw[high] - sw[low]);
        int dw = sw[high] + (low > 0 ? sw[low - 1] : 0);
        for (int j = low + 1; j <= high ; ++j)
        {
            if (fabs(dw - sw[j] - sw[j - 1]) < min)
            {
                i = j;
                min = fabs(dw - sw[j] - sw[j - 1]);
            }
        }

        T = (TNode*)malloc(sizeof(TNode));
        T->data = R[i];
        if (i == low)
            T->lchild = nullptr;
        else
            CreateSecondOptimal(T->lchild,R,sw,low,i-1);

        if (i == high)
            T->rchild = nullptr;
        else
            CreateSecondOptimal(T->rchild,R,sw,i + 1, high);
    }


};

#endif //DATASTRUCTURE_STATICSEARCHTREE_H











