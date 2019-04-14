//
// Created by caichao on 2019-04-05.
//

#ifndef DATASTRUCTURE_BALANCEDBINARYTREE_H
#define DATASTRUCTURE_BALANCEDBINARYTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <cmath>

//https://blog.csdn.net/qq_29542611/article/details/80136574

class BalancedBinaryTree
{
public:

    static void Test()
    {
        BalancedBinaryTree tree;
        char data[10] = {'a','b','c','d','e','f','g','h','i','j'};
        for (int i = 0; i < 10; ++i)
        {
            bool taller = false;
            tree.InsertAVL(tree._root,i,data[i],taller);
        }

        if (tree._root)
        {

        }
    }

    static  const int LH = 1;
    static  const int EH = 0;
    static  const int RH = -1;

    struct Node{
        int key = 0;
        char data;
        int bf = 0; //平衡因子
        Node *lchild = nullptr;
        Node *rchild = nullptr;
    };

    Node *_root = nullptr;

    void R_Rotate(Node *&p)
    {
        Node *lc = p->lchild;
        p->lchild = lc->rchild;
        lc->rchild = p;
        p = lc;
    }

    void L_Rotate(Node *&p)
    {
        Node *rc = p->rchild;
        p->rchild = rc->lchild;
        rc->lchild = p;
        p = rc;
    }

    void LeftBalance(Node *&t)
    {
        Node *lc = t->lchild;
        switch (lc->bf)
        {
            case LH: //插入点在左孩子的左子树
            {
                t->bf = lc->bf = EH;
                R_Rotate(t);
            }
                break;
            case RH: //插入点在左孩子的右子树
            {
                Node *rd = lc->rchild;
                switch (rd->bf)
                {
                    case LH:
                        t->bf = RH;
                        lc->bf = EH;
                        break;
                    case EH:
                        t->bf = lc->bf = EH;
                        break;
                    case RH:
                        t->bf = EH;
                        lc->bf = LH;
                        break;
                }
                rd->bf = EH;
                L_Rotate(t->lchild);
                R_Rotate(t);
            }
                break;

        }
    }

    void RightBalance(Node *&t)
    {
        Node *rc = t->rchild;
        switch (rc->bf)
        {
            case RH:
            {
                t->bf = rc->bf = EH;
                L_Rotate(t);
            }
                break;
            case LH:
            {
                Node *ld = rc->lchild;
                switch (ld->bf) //考虑三种情况旋转后的结果
                {
                    case LH:
                    {
                        t->bf = EH;
                        rc->bf = RH;
                    }
                        break;
                    case EH:
                    {
                        t->bf = rc->bf = EH;
                    }
                        break;
                    case RH:
                    {
                        t->bf = LH;
                        rc->bf = EH;
                    }
                        break;
                }
                ld->bf = EH;
                R_Rotate(t->rchild);
                L_Rotate(t);
            }
                break;

        }
    }

    bool InsertAVL(Node *&T,int key,char data,bool &taller)
    {
        if (!T) //初始化节点
        {
            T = (Node*)malloc(sizeof(Node));
            T->key = key;
            T->data = data;
            T->lchild = T->rchild = nullptr;
            T->bf = EH;
            taller = true;
        }
        else
        {
            if (key == T->key) //未插入任何节点
            {
                taller = false;
                return false;
            }
            if (key < T->key) //递归向左搜索
            {
                if (!InsertAVL(T->lchild,key,data,taller))
                    return false;
                //tree balance
                if (taller) //左子树变高
                {
                    switch (T->bf)
                    {
                        case LH: //原来左子树比右子树高,插入节点后变成了2
                        {
                            LeftBalance(T);
                            taller = false;
                        }
                            break;
                        case EH: //插入后变成 1
                        {
                            T->bf = LH;
                            taller = true;
                        }
                            break;
                        case RH: //插入后变成平衡
                        {
                            T->bf = EH;
                            taller = false;
                        }
                            break;
                    }
                }
            }
            else
            {
                if(!InsertAVL(T->rchild,key,data,taller))
                    return false;
                if (taller) //在右子树插入节点
                {
                    switch (T->bf) //
                    {
                        case LH:
                        {
                            T->bf = EH;
                            taller = false;
                        }
                            break;
                        case EH:
                        {
                            T->bf = RH;
                            taller = true;
                        }
                            break;
                        case RH: //右子树变成2
                        {
                            RightBalance(T);
                            taller = false;
                            break;
                        }
                            break;
                    }
                }
            }
        }
        return true;
    }

};

#endif //DATASTRUCTURE_BALANCEDBINARYTREE_H
