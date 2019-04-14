//
// Created by caichao on 2019-03-24.
//

#ifndef DATASTRUCTURE_CROSSLIST_H
#define DATASTRUCTURE_CROSSLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class CrossList
{
public:

    static void Test()
    {
        float mat1[2][3] = {
            {1,2,3},
            {0,3,0}
        };
        CrossList crossList((float**)mat1,2,3);
        crossList.Log();
    }

    CrossList(float **array , int rows, int cols){

        this->rows = rows;
        this->cols = cols;
        rhead = (Node**)malloc(rows * sizeof(Node*));
        for (int k = 0; k < rows; ++k)
        {
            rhead[k] = nullptr;
        }
        chead = (Node**)malloc(cols * sizeof(Node*));

        for (int l = 0; l < cols; ++l)
        {
            chead[l] = nullptr;
        }

        for (int j = 0; j < rows ; ++j)
        {
            Node *nodeRHead = rhead[j];

            for (int i = 0; i < cols; ++i)
            {
                Node *nodeChead = chead[i];
                float v = *((float*)array + cols * j + i);
                if(v)
                {
                    Node *node = new Node;
                    node->row = i;
                    node->col = j;
                    node->e = v;

                    if (nodeChead)
                    {
                        while (nodeChead->down && nodeChead->row < j) //找到当前行中，col刚好等于插入节点的位置
                        {
                            nodeChead = nodeChead->down;
                        }
                        node->down = nodeChead->down;
                        nodeChead->down = node;
                        nodeChead = chead[i];
                    }
                    else
                    {
                        chead[i] = node;
                        nodeChead = node;
                    }


                    if (nodeRHead)
                    {
                        while (nodeRHead->right && nodeRHead->col < i)
                        {
                            nodeRHead = nodeRHead->right;
                        }
                        node->right = nodeRHead->right;
                        nodeRHead->right = node;
                        nodeRHead = rhead[j];
                    }
                    else
                    {
                        rhead[j] = node;
                        nodeRHead = node;
                    }

                    ++tu;
                }
            }
        }

        //fin
        if (1){}

    }

    void Log()
    {
        printf("down \n");
        for (int i = 0; i < cols; ++i)
        {
            Node *node = chead[i];
            while (node)
            {
                printf("%d %d %.0f->",node->row,node->col,node->e);
                node = node->down;
            }
            printf("\n");
        }

        printf("\n\n");

        printf("right \n");
        for (int j = 0; j < rows; ++j)
        {
            Node *node = rhead[j];
            while (node)
            {
                printf("%d %d %.0f->",node->row,node->col,node->e);
                node = node->right;
            }
            printf("\n");
        }
    }

private:
    struct Node{
        int row = 0;
        int col = 0;
        float e = 0;
        Node *right = nullptr;
        Node *down = nullptr;
    };
    int rows = 0;
    int cols = 0;
    int tu = 0;
    Node **rhead = nullptr;
    Node **chead = nullptr;
};

#endif //DATASTRUCTURE_CROSSLIST_H
