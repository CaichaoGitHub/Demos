//
// Created by caichao on 2019-04-08.
//

#ifndef DATASTRUCTURE_QUICKSORT_H
#define DATASTRUCTURE_QUICKSORT_H

#include <stdio.h>
#include <stdlib.h>
#include <cmath>

class QuickSort
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
//        BubbleSort(sqlist);
//        QSort(sqlist,1,sqlist.length);
//        SelectSort(sqlist);
//        HeapSort(sqlist);
        MergeSort(sqlist);
    }
    
    static void BubbleSort(Sqlist &l)
    {
        int tmp = 0;
        for (int i = 0; i < l.length - 1; ++i)
        {
            for (int j = 0; j < l.length - 1 - i; ++j) //一次气泡，将最大值后移
            {
                if (l.data[j] > l.data[j + 1])
                {
                    tmp = l.data[j];
                    l.data[j] = l.data[j + 1];
                    l.data[j + 1] = tmp;
                }
            }
            WalkThrough(l); //o(n2)
        }
    }

    static void QSort(Sqlist &l, int low , int high)
    {
        if (low < high)
        {
            int pivotloc = Partition(l,low,high);
            QSort(l,low,pivotloc-1); //排序低的那一部分
            QSort(l,pivotloc + 1, high); //排序高的那一部分
            WalkThrough(l);
        }
    }

    static int Partition(Sqlist &l,int low, int high)
    {
        l.data[0] = l.data[low]; //以low点进行分割，分别将大的移动到右边，小的移动到左边
        int pivotkey = l.data[low];
        while (low < high)
        {
            while (low < high && l.data[high] >= pivotkey) //从高位查找第一个小于pivotkey的数据
                --high;
            l.data[low] = l.data[high];
            while (low < high && l.data[low] <= pivotkey) //从低位查找第一个大于 pivotkey的数据
                ++low;
            l.data[high] = l.data[low];
        }
        l.data[low] = l.data[0];

        return low; //新的分割点
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

    static void SelectSort(Sqlist &l)
    {
        for (int i = 1; i < l.length; ++i)
        {
            int j = SelectMinKey(l,i);
            if (i != j)
            {
                int tmp = l.data[i];
                l.data[i] = l.data[j];
                l.data[j] = tmp;
            }
            WalkThrough(l);
        }
    }

    static int SelectMinKey(Sqlist &l, int i )
    {
        int min = l.data[i];
        int idx = i;
        for (int j = i + 1; j < l.length; ++j)
        {
            if (l.data[j] < min)
            {
                min = l.data[j];
                idx = j;
            }
        }
        return idx;
    }

    static void HeadAdjust(Sqlist &l, int s, int m) //建立大顶堆
    {
        int rc = l.data[s]; //处理 s 的 子 节点
        for (int j = 2 * s; j <= m; j *= 2) //考虑 k(i) > k(2i) && k(i) > k(2i + 1) || k(i) < k(2i) && k(i) < k(2i + 1)
        {
            if (j < m && l.data[j] < l.data[j + 1]) //如果左孩子小于右孩子，将j 指向大的孩子
                ++ j;
            if (rc > l.data[j]) // 如果 要更新的 rc 大于 j 孩子，那么这个位置就是rc 的插入位置
                break;
            l.data[s] = l.data[j]; //rc < j, rc 还需要下移动，j 向上移动
            s = j; //更新插入位置
        }
        l.data[s] = rc; //插入 rc
    }

    static void HeapSort(Sqlist &l)
    {
        for (int i = l.length / 2; i > 0 ; --i) //将i ...length 建立成大顶堆,最后一个非终端节点是[n/2] , 所以只需要对 [n/2] 做堆排序
        {
            HeadAdjust(l,i,l.length);
        }

        for (int j = l.length; j > 1 ; --j)
        {
            int tmp = l.data[j];
            l.data[j] = l.data[1]; //将大的元素放到末尾
            l.data[1] = tmp; //将末尾元素提前
            HeadAdjust(l,1,j-1); //进行堆排序
            WalkThrough(l);
        }
    }

    static void Merge(Sqlist &sr,Sqlist &tr, int i, int m ,int n)
    {
        int j,k;
        for (j = m + 1,k = i ; i <= m && j <= n; ++k) //合并2个有序序列到单独的一个列表
        {
            if (sr.data[i] < sr.data[j]) //将左右序列按照升序填写到 tr 中， 这个也即归并
                tr.data[k] = sr.data[i++];
            else
                tr.data[k] = sr.data[j++];
        }
        for (int l = i; l <= m; ++l) //cp 未 完成的 数据
        {
            tr.data[k++] = sr.data[l];
        }

        for (int q = j; q <= n; ++q)
        {
            tr.data[k++] = sr.data[q];
        }
    }

    static void MSort(Sqlist &sr, Sqlist &tr,int s, int t)
    {
        if (s == t)
            tr.data[s] = sr.data[s];
        else //对有序序列
        {
            int m = (s + t) / 2;
            Sqlist tr2; //先做 2 -> 4 -> 8
            MSort(sr,tr2,s,m); //对子序列执行归并(s,m)
            MSort(sr,tr2,m + 1, t); //对子序列 (m + 1, t)
            Merge(tr2,tr,s,m,t); // 对 子序列 (s,m) & (m + 1, t) 进行归并
        }
    }

    static void MergeSort(Sqlist &l)
    {
        Sqlist tr;
        MSort(l,l,1,l.length - 1);
        WalkThrough(l);
    }

};

#endif //DATASTRUCTURE_QUICKSORT_H





















