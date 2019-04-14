//
// Created by caichao on 2019-03-26.
//

#ifndef DATASTRUCTURE_HUFFMANTREE_H
#define DATASTRUCTURE_HUFFMANTREE_H

#include <stdlib.h>
#include <iostream>

class HuffmanTree
{
public:

    typedef struct {
        int weight;
        int parent,lchild,rchild;
    }HTNode, *HuffmanTr;

    static void Test()
    {
        HuffmanTree tree;

        int weight[5] = {1,5,3,2,4};
        tree.CreateTree(weight,5);
        tree.Log(tree.tree_);
    }

    HuffmanTree(){}
    ~HuffmanTree(){}

    void CreateTree(int weight[],int n) //输入N个叶子节点的权重
    {
        int maxCountNode = 2 * n - 1; //总节点数
        len_ = maxCountNode;
        tree_ = (HuffmanTr)malloc(sizeof(HTNode) * maxCountNode);
        for (int i = 0; i < n; ++i)
        {
            tree_[i] = {weight[i],-1,-1,-1};
        }
        for (int j = n; j < maxCountNode; ++j)
        {
            tree_[j] = {0,-1,-1,-1};
        }

        for (int k = n; k < maxCountNode; ++k)
        {
            int s1,s2;
            Select(tree_,k,s1,s2);
            HTNode &node1 = tree_[s1];
            HTNode &node2 = tree_[s2];
            HTNode &node3 = tree_[k];

            node1.parent = k;
            node2.parent = k;

            node3.lchild = s1;
            node3.rchild = s2;
            node3.weight = node1.weight + node2.weight;
        }

        //traverse

        char *ch = (char*)malloc(sizeof(char) * n);
        ch[n - 1] = '\0';
        for (int l = 0; l < n; ++l)
        {
            int start = n - 1;
            for (int i = l, f = tree_[l].parent; f != -1 ; i = f, f = tree_[f].parent)
            {
                if (tree_[f].lchild == i)
                    ch[--start] = '0';
                else
                    ch[--start] = '1';
            }
            printf("%s \n",ch + start);
        }
    }

    void Log(HuffmanTr &tree)
    {
        for (int i = 0; i < len_; ++i)
        {
            HTNode &node = tree[i];
            std::cout << "idx" << i << " w:" << node.weight << " p:" << node.parent << " l:" << node.lchild << " r:" << node.rchild << std::endl;
        }
    }

    void Select(HuffmanTr &tree ,  int end, int &node1,int &node2)
    {
        HTNode *minPtr[2] = {NULL};

        for (int i = 0; i < end; ++i)
        {
            HTNode &node = tree[i];
            if (node.parent == -1)
            {
                if (minPtr[0] && minPtr[1])
                {
                    if (minPtr[0]->weight > node.weight || minPtr[1]->weight > node.weight)
                    {
                        if (minPtr[0]->weight > minPtr[1]->weight)
                        {
                            minPtr[0] = &node;
                            node1 = i;
                        }
                        else
                        {
                            minPtr[1] = &node;
                            node2 = i;
                        }
                    }
                }
                else
                {
                    if (minPtr[0] == NULL)
                    {
                        minPtr[0] = &node;
                        node1 = i;
                    }

                    else if (minPtr[1] == NULL)
                    {
                        minPtr[1] = &node;
                        node2 = i;
                    }

                }
            }
        }
    }

private:

    int len_ = 0;
    HuffmanTr tree_ = nullptr;
};

#endif //DATASTRUCTURE_HUFFMANTREE_H
