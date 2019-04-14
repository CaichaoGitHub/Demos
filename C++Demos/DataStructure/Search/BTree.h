//
// Created by caichao on 2019-04-06.
//

#ifndef DATASTRUCTURE_BTREE_H
#define DATASTRUCTURE_BTREE_H

#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class BTree //B- 树
{
public:

    static const int m = 3;
    typedef int KeyType;

    typedef struct BMTNode{
        int keynum = 0; //关键字数量
        BMTNode *parent = nullptr; //父节点
        KeyType key[m + 1]; //关键字
        BMTNode *ptr[m + 1]; //子节点
        int *recptr[m + 1];
    }*BMT;

    BMT head = nullptr;

    static void Test()
    {
        BTree tree;

        int data[11] = {45,24,53,90,3,12,37,50,61,70,100};

        for (int i = 0; i < 11; ++i)
        {
            tree.BMTInsertKey(tree.head,data[i]);
        }
//        tree.BMTWalkThrough(tree.head);
        tree.BMTDeleteKey(tree.head,12);
        tree.BMTDeleteKey(tree.head,50);
        tree.BMTDeleteKey(tree.head,53);
    }

    void BMTWalkThrough(BMT & T)
    {
        using namespace std;
        if(!T) return;
        static int depth = 0;
        ++depth;

        int index = 0;
        bool running = true;
        while(running) {
            cout << "Cur depth: " << depth << endl;
            cout << "Cur Pos: " << (void*)T << ";  "
                 << "Keynum: " << T->keynum << "; " << endl;
            cout << "Index: " << index << ";  Key: " << T->key[index] << endl;

            int ans = 0;
            do{
                cout << "1.Prev Key; 2.Next Key; 3.Deepen Left; 4.Deepen Right; 5.Backup" << endl;
                cin >> ans;
                if(1 <= ans && ans <= 5)
                    break;
            }while(true);

            switch(ans) {
                case 1:
                    if(index == 0)
                        cout << "Failed." << endl;
                    else
                        --index;
                    break;
                case 2:
                    if(index == T->keynum)
                        cout << "Failed" << endl;
                    else
                        ++index;
                    break;
                case 4:
                    if(index > 0 && T->ptr[index])
                        BMTWalkThrough(T->ptr[index]);
                    else
                        cout << "Failed" << endl;
                    break;
                case 3:
                    if(index > 0 && T->ptr[index-1])
                        BMTWalkThrough(T->ptr[index-1]);
                    else
                        cout << "Failed" << endl;
                    break;
                case 5:
                    running = false;
                    break;
            }//endsw
        }//endw

        --depth;
    }

    bool BMTDeleteKey(BMT &T, KeyType K)
    {
        BMTNode *curNode = nullptr;
        int curIdx = 0;
        if (BMTSearchKey(T,K,curNode,curIdx))
        {
            BMTDelete(T,curNode,curIdx);
            return true;
        }
        return false;
    }

    bool BMTInsertKey(BMT &T, KeyType K)
    {
        BMTNode *curNode = nullptr;
        int preIdx = 0;
        if (BMTSearchKey(T,K,curNode,preIdx)) //search key
        {
            return false;
        }
        else //key not found
        {
            KeyType  curK = K;
            BMTNode *rhs = nullptr;
            bool finished = false;
            while (curNode && !finished)
            {
                //insert new K at preIdx of curNode, insert node rhs
                BMTInsert(curNode,preIdx,curK,rhs);
                if (curNode->keynum < m) //maximum m child tress,means m-1 keys
                {
                    finished = true;
                }
                else
                {
                    int s = ceil((float)m/2.0);
                    if (!BMTSplit(curNode,s,rhs,curK)) //split from s which is the minimum node size, return cur k as the spilt node
                    {
                        return false;
                    }

                    if (curNode->parent == nullptr) //no parent , we should create new node for curK
                        break;
                    else //try to insert curK to parent
                    {
                        curNode = curNode->parent;
                        preIdx = BMTSearch(curNode,curK);
                    }
                }
            }
            if (!finished && !BMTNewRoot(T,curNode,curK,rhs)) //if not finished, we should create a new node for curK at Node T with lchild and rchild
            {
                printf("failed to create new node \n");
            }
        }
        return true;
    }

    bool BMTSearchKey(BMT &t, KeyType k , BMTNode *&recNode, int &recIdx)
    {
        recIdx = 0;
        recNode = nullptr;
        BMTNode *curNode = t;
        while (curNode)
        {
            recIdx = BMTSearch(curNode,k);
            if(recIdx > 0 && curNode->key[recIdx] == k) //在当前节点搜索到
            {
                recNode = curNode; //searched node
                return true;
            }
            else
            {
                recNode = curNode; //从当前节点向下搜索区间
                curNode = curNode->ptr[recIdx];
            }
        }
        return false;
    }

    void BMTDelete(BMT &T, BMT  curNode,int curIdx)
    {
        if (curIdx < 0 || curIdx > curNode->keynum)
            return;

        while (true)//循环到叶子节点
        {
            if (curNode->ptr[curIdx - 1] && curNode->ptr[curIdx]) //非叶子节点
            {
                //左孩子的关键字数量大于右孩子
                if (curNode->ptr[curIdx - 1]->keynum > curNode->ptr[curIdx]->keynum)
                {
                    //将左孩子的最后一个关键字移动到父节点，也即删除节点的
                    //左孩子的最大的关键字移动到父节点作为父节点，父节点的关键字为空
                    BMT lhs = curNode->ptr[curIdx - 1];
                    curNode->key[curIdx] = lhs->key[lhs->keynum];
                    curNode = lhs;
                    curIdx = lhs->keynum;
                }
                else
                {
                    //将右孩子的最小的关键字移动给父节点,将要删除的节点指向子节点
                    BMT  rhs = curNode->ptr[curIdx];
                    curNode->key[curIdx] = rhs->key[1];
                    curNode = rhs; curIdx = 1;
                }
            }
            else if (!curNode->ptr[curIdx - 1] && !curNode->ptr[curIdx]) //叶子节点
            {
                //前移关键字，删除curIdx 关键字
                for (int i = curIdx; i <= curNode->keynum ; ++i)
                {
                    curNode->key[i] = curNode->key[i + 1];
                }

                --curNode->keynum;

                BMTDeleteBalance(T,curNode);

                break;
            }
            else
            {
                printf("error \n");
            }
        }
        return;
    }

    void BMTDeleteBalance(BMT &t,BMT curNode)
    {
        int lb = ceil((float)m / 2.0);
        BMT parent = curNode->parent;
        //判断节点的keynum 是否ok
        while (parent && curNode->keynum < lb)
        {
            int idx = 0;

            //find the node to balane
            for (int i = 0; i <= parent->keynum; ++i)
            {
                if (parent->ptr[i] == curNode)
                {
                    idx = i;
                    break;
                }
            }

            //左右兄弟
            BMT lsilb = NULL,rsilb = NULL;

            if (idx - 1 >= 0)
                lsilb = parent->ptr[idx - 1];
            if (idx + 1 <= parent->keynum)
                rsilb = parent->ptr[idx + 1];

            //adjust
            if (rsilb && rsilb->keynum > lb) //右兄弟的keynum 大于最小数量
            {
                BMTRotateLeft(parent,idx,curNode,rsilb);
            }
            else if (lsilb && lsilb->keynum > lb)
            {
                BMTRotateRight(parent,idx,curNode,lsilb);
            }
            else //关键字数量不够，那么需要进行合并
            {
                if (lsilb) //存在左兄弟
                    BMTMerge(parent,idx,lsilb,curNode);
                else //存在右兄弟
                    BMTMerge(parent,idx + 1, curNode,rsilb);
                curNode = parent;
                parent = curNode->parent;
            }

        }

        if (curNode->keynum == 0)
        {
            t = curNode->ptr[0];
            delete curNode;
        }
    }

    //将兄弟节点中最小的关键字上移到双亲节点，而将双亲节点中靠近上移关键字的关键字下移动到被删关键字的节点
    /**
     * \param parent, parent node of cur and rslib
     * \param idx , cur index in parent ptr
     * \param cur, node to delete
     * \param rsilb, cur's right brother
     * */
    void BMTRotateLeft(BMT parent, int idx, BMT cur, BMT rsilb)
    {
        //将父节点的最小key 下移到要删除的节点
        cur->key[cur->keynum + 1] = parent->key[idx + 1];
        //将有兄弟的第一个指针移动过来,
        cur->ptr[cur->keynum + 1] = rsilb->ptr[0];

        if (cur->ptr[cur->keynum + 1])
            cur->ptr[cur->keynum + 1]->parent = cur;
        rsilb->ptr[0] = nullptr;
        ++cur->keynum;

        //右孩子的第一个key上移
        parent->key[idx + 1] = rsilb->key[1];
        rsilb->key[idx] = 0;

        //
        for (int i = 0; i < rsilb->keynum; ++i)
        {
            rsilb->key[i] = rsilb->key[i + 1];
            rsilb->ptr[i] = rsilb->ptr[i + 1];
        }
        rsilb->key[0] = 0;
        --rsilb->keynum;
    }

    void BMTRotateRight(BMT parent,int idx, BMT cur, BMT lsilb)
    {
        for (int i = cur->keynum; i >= 0 ; --i)
        {
            cur->key[i + 1] = cur->key[i];
            cur->ptr[i + 1] = cur->ptr[i];
        }

        cur->key[1] = parent->key[idx];
        cur->ptr[0] = lsilb->ptr[lsilb->keynum];
        if (cur->ptr[0])
            cur->ptr[0]->parent = cur;
        lsilb->ptr[lsilb->keynum] = NULL;
        ++ cur->keynum;

        parent->key[idx] = lsilb->key[lsilb->keynum];
        lsilb->key[lsilb->keynum] = 0;

        --lsilb->keynum;
    }

    void BMTMerge(BMT parent, int idx, BMT lsilb, BMT cur)
    {
        for (int i = 0; i <= cur->keynum ; ++i)
        {
            //将cur节点的key 合并到 lsib中
            lsilb->key[lsilb->keynum + 1 + i] = cur->key[i];
            lsilb->ptr[lsilb->keynum + 1 + i] = cur->ptr[i];
            if (lsilb->ptr[lsilb->keynum + 1 + i])
                lsilb->ptr[lsilb->keynum + 1 + i] = lsilb;
        }
        //将父节点的最后一个节点合并到lsilb中
        lsilb->key[lsilb->keynum + 1] = parent->key[idx];
        lsilb->keynum = lsilb->keynum + cur->keynum + 1;

        delete cur;
        for (int j = 0; j < parent->keynum; ++j)
        {
            parent->key[j] = parent->key[j + 1];
            parent->ptr[j] = parent->ptr[j + 1];
        }
        -- parent->keynum;
    }

    void BMTInsert(BMT &t , int i , KeyType K , BMTNode *rhs)
    {
        //move backward
        for (int j = t->keynum; j >= i + 1 ; --j)
        {
            t->key[j + 1] = t->key[j];
            t->ptr[j + 1] = t->ptr[j];
        }

        //insert new data
        t->key[i + 1] = K;
        t->ptr[i + 1] = rhs;
        ++t->keynum;
    }

    int BMTSearch(BMT &t, KeyType K) //在节点的m key 中搜索
    {
        int i = 0;
        for (int j = 1; j <= t->keynum; ++j)
        {
            if(t->key[j] <= K)
                i = j;
        }
        return i;
    }

    /**
     * split t at s with right hand side stored in rhs, and return key[s] by key
     * * */
    bool BMTSplit(BMT &t , int s , BMT &rhs, KeyType &midK)
    {
        rhs = new BMTNode;
        memset(rhs->key,0, sizeof(rhs->key));
        memset(rhs->ptr,0, sizeof(rhs->ptr));
        rhs->parent = t->parent;
        midK = t->key[s];
        t->key[s] = 0;

        rhs->ptr[0] = t->ptr[s]; //分裂s
        if (rhs->ptr[0]) //更新rhs 子节点的parent 为自己
            rhs->ptr[0]->parent = rhs;
        t->ptr[s] = nullptr;
        //将s右边的key ptr 移给 新的 rhs 节点
        for (int i = 1; i <= m - s; ++i)
        {
            rhs->key[i] = t->key[s + i];
            t->key[s + i] = 0;
            rhs->ptr[i] = t->ptr[s + i];
            t->ptr[s + i] = nullptr;
            if (rhs->ptr[i]) //更新parent
                rhs->ptr[i]->parent = rhs;
        }

        //更新key num
        rhs->keynum = m - s;
        t->keynum = s - 1;
        return true;
    }

    bool BMTNewRoot(BMT &t,BMT &lhs, KeyType midK, BMT &rhs)
    {
        BMT tmp = new BMTNode;
        memset(tmp->key,0, sizeof(tmp->key));
        memset(tmp->ptr,0, sizeof(tmp->ptr));
        tmp->keynum = 1;
        tmp->key[1] = midK;
        tmp->ptr[0] = lhs;
        if (lhs)
            lhs->parent = tmp;
        tmp->ptr[1] = rhs;
        if (rhs)
            rhs->parent = tmp;
        t = tmp;
        return true;
    }
};

#endif //DATASTRUCTURE_BTREE_H
