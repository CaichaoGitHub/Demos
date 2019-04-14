//
// Created by caichao on 2019-04-07.
//

#ifndef DATASTRUCTURE_INSERTIONSORT_H
#define DATASTRUCTURE_INSERTIONSORT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class InsertionSort
{
public:
    static const int maxSize = 20;
    typedef struct {
        int data[maxSize + 1] = {0};
        int length;
    }Sqlist;

    static void Test()
    {
        Sqlist sqlist;
        sqlist.length = 10 + 1;
        int data[] = {49,38,65,97,76,13,27,49,55,04};
        for (int i = 1; i < sqlist.length + 1; ++i)
        {
            sqlist.data[i] = data[i-1];
        }

//        InsertionSort::InsertSort(sqlist);
//        InsertionSort::BInsertSort(sqlist);
        int dlta[] = {4,3,1};
        InsertionSort::ShellSort(sqlist,dlta,4);
    }

    static void WalkThrough(Sqlist &l)
    {
        printf("\n");
        for (int i = 1; i < l.length; ++i)
        {
            printf("%d ",l.data[i]);
        }

        printf("\n");
    }
    
    //直接插入排序
    static void InsertSort(Sqlist &l)
    {
        //顺序不对->找位置->腾空间->插入
        for (int i = 2; i <l.length ; ++i)
        {
            if (l.data[i] < l.data[i - 1]) //如果data at i 小于 data at i - 1
            {
                l.data[0] = l.data[i]; //保存到 0 ,哨兵，将 l.i-1 复制到 l.i
                l.data[i] = l.data[i - 1];
                int j;
                for (j = i - 2; j >= 0 && l.data[0] < l.data[j]; --j) //对前面已经排序过表，给新的哨兵腾出位置
                {
                    l.data[j + 1] = l.data[j];
                }
                l.data[j + 1] = l.data[0]; //插入
            }
            WalkThrough(l);
        }
    }

    //二分插入排序
    static void BInsertSort(Sqlist &l)
    {
        for (int i = 2; i < l.length; ++i)
        {
            l.data[0] = l.data[i];
            int low = 1;
            int high = i - 1;
            while (low <= high) //二分搜索插入位置
            {
                int mid = (low + high) / 2;
                if (l.data[0] < l.data[mid])
                    high = mid - 1;
                else
                    low = mid + 1;
            }
            for (int j = i - 1; j >= high + 1 ; --j) //后移数据，腾空间
            {
                l.data[j + 1] = l.data[j];
            }
            l.data[high + 1] = l.data[0]; //插入
            WalkThrough(l);
        }
    }

    //将序列分割成多个子序列，然后进行插入排序，最后再进行一趟插入排序，由于序列基本有序，减少了元素移动的量，
    static void ShellSort(Sqlist &l,int dlta[],int t)
    {
        for (int i = 0; i < t; ++i)
        {
            ShellInsert(l,dlta[i]);
        }
    }

    static  void ShellInsert(Sqlist &l, int dk)
    {
        for (int i = dk + 1; i < l.length; ++i) //分段移动
        {
            if (l.data[i] < l.data[i - dk])
            {
                l.data[0] = l.data[i];
                l.data[i] = l.data[i - dk];
                int j ;
                for (j = i - dk; l.data[0] < l.data[j]; j -= dk)
                {
                    l.data[j + dk] = l.data[j];
                }
                l.data[j + dk] = l.data[0];
            }
            WalkThrough(l);
        }
    }

};

#endif //DATASTRUCTURE_INSERTIONSORT_H










