//
// Created by caichao on 2019-04-11.
//

#ifndef DATASTRUCTURE_RADIXSORT_H
#define DATASTRUCTURE_RADIXSORT_H

#include <stdio.h>
#include <stdlib.h>

class Radixsort
{
public:
    static const int MAX_NUM_OF_KEY = 8;
    static const int RADIX = 10;
    static const int MAX_SPACE = 1000;
    typedef int KeysType;
    typedef struct {
        KeysType keys[MAX_NUM_OF_KEY];
        int next;
    }SLCell;
    typedef struct {
        SLCell r[MAX_SPACE];
        int keynum;
        int recnum;
    }SLList;
    typedef int ArrType[RADIX];

    static void Test()
    {
        SLList list;
        FILE *file = fopen("s1.txt","r");
        fscanf(file,"%d%d",&list.keynum,&list.recnum);
        for (int i = 1; i <= list.recnum; ++i)
        {
            for (int j = 0; j < list.keynum; ++j)
            {
                fscanf(file," %d",&list.r[i].keys[j]);
            }
        }
        Sort(list);
        fclose(file);
    }

    static void Distribute(SLCell r[] , int i, ArrType &f, ArrType &e)
    {
        for (int j = 0; j < RADIX; ++j)
        {
            f[j] = 0;
            e[j] = 0;
        }

        for (int p = r[0].next; p  ; p = r[p].next) // 遍历连表，将value以关键字分别排序到 f 和 e , f 指向头部， e 指向尾部
        {
            int j = r[p].keys[i];
            if (!f[j])
                f[j] = p; //f[j]
            else
                r[e[j]].next = p; //将e[j]指向数据的next 指向 p
            e[j] = p; //e[j] 指向 p
        }
    }

    static void Collect(SLCell r[],int i, ArrType &f, ArrType &e)
    {
        int j;
        for (j = 0; !f[j]; ++j) //find first none empty list
        {

        }

        r[0].next = f[j]; //r[0].next point to f[j]
        int t = e[j]; // t means tail
        while (j < RADIX - 1)
        {
            for (++j; j < RADIX - 1 && !f[j]; ++j) //find next none empty list
            {

            }
            if (f[j]) //将连表重新连接
            {
                r[t].next = f[j];
                t = e[j];
            }
        }
        r[t].next = 0;
    }

    static void Sort(SLList &l)
    {
        for (int i = 0; i < l.recnum; ++i) //将列表首位相连
        {
            l.r[i].next = i + 1;
        }

        l.r[l.recnum].next = 0;

        for (int j = l.keynum - 1; j >= 0; --j)
        {
            ArrType f,e;
            Distribute(l.r,j,f,e);
            Collect(l.r,j,f,e);
            WalkThrough(l);
        }
    }

    static void WalkThrough(SLList &l)
    {
        printf("\n");
        for (int i = l.r[0].next; i ; i = l.r[i].next)
        {
            auto &keys = l.r[i].keys;
            printf("%d%d%d->",keys[0],keys[1],keys[2]);
        }
        printf("\n");
    }
};

#endif //DATASTRUCTURE_RADIXSORT_H
