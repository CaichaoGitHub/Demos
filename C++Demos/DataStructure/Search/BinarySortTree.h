//
// Created by caichao on 2019-04-05.
//

#ifndef DATASTRUCTURE_BINARYSORTTREE_H
#define DATASTRUCTURE_BINARYSORTTREE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class BinarySortTree //search and insert
{
public:

    struct Node{
        int key;
        int data;
        Node *lchild = nullptr;
        Node *rchild = nullptr;
    };

    Node *root = nullptr;

    static  void Test()
    {
        BinarySortTree tree;
        FILE *file = fopen("s1.txt","r");
        int vcount;
        fscanf(file," %d", &vcount);

        for (int i = 0; i < vcount; ++i)
        {
            int key,value;
            fscanf(file," %d %d",&key,&value);
            tree.InsertBST(tree.root,key,value);
        }

        tree.DeleteBST(tree.root,12);
    }

    //二叉树
    bool SearchBST(Node *&tree,int key,Node *f,Node *&p)
    {
        if(!tree)
        {
            p = f; //未找到，设置p为父节点
            return false;
        }
        else if (key == tree->key)
        {
            p = tree; //找到
            return true;
        }
        else if (key < tree->key)
        {
            return SearchBST(tree->lchild,key,tree,p); //向左搜索
        }
        else //向右搜索
        {
            return SearchBST(tree->rchild,key,tree,p);
        }
    }

    bool InsertBST(Node *& root,int key,int data)
    {
        Node *p = nullptr;
        if (!SearchBST(root,key, nullptr,p))
        {
            Node *s = (Node*)malloc(sizeof(Node));
            s->data = data;
            s->key = key;
            s->lchild = s->rchild = nullptr;

            if (!p)
                root = s;
            else if (key < p->key) //插入左孩子
                p->lchild = s;
            else //插入右孩子
                p->rchild = s;
            return true;
        }
        return false;
    }

    bool DeleteBST(Node *&tree, int key)
    {
        if (!tree)
            return false;
        if (key == tree->key) //递归搜索树节点
            Delete(tree);
        else if (key < tree->key)
            DeleteBST(tree->lchild,key);
        else
            DeleteBST(tree->rchild,key);
    }

    bool Delete(Node *&p)
    {
        if (!p->rchild) //右孩子空
        {
            Node *q = p;
            p = p->lchild;
            free(q);
        }
        else if (!p->lchild) //左孩子空
        {
            Node *q = p;
            p = p->rchild;
            free(q);
        }
        else
        {
            Node *q = p;
            Node *s = p->lchild;
            while (s->rchild) //第二种链接方案，将删除节点的左孩子的右子树的最后一个节点放到删除位置
            {
                q = s;
                s = s->rchild; //找到右子树的最后一个孩子
            }
            p->data = s->data; //直接移动数据，省去调整节点位置的逻辑
            p->key = s->key;
            //s 已经移动到最后了，只有左子树，需要链接左子树到前一个q节点
            if (q != p) //如果最后一个Q不等于P节点，那么q在右子树，直接将s的左子树链接到q的右子树
                q->rchild = s->lchild;
            else //如果q是p节点，那么需要将s的左子树，链接到q的左子树
                q->lchild = s->lchild;
            free(s); //释放s

        }
    }

};

#endif //DATASTRUCTURE_BINARYSORTTREE_H
