//
// Created by caichao on 2019-04-05.
//

#ifndef DATASTRUCTURE_BINARYSEARCH_H
#define DATASTRUCTURE_BINARYSEARCH_H

#include <stdlib.h>
#include <stdio.h>

class BinarySearch
{

    static const int _maxSize = 20;

public:
    static void Test()
    {
        BinarySearch binarySearch;
        binarySearch.Create();
        binarySearch.BSearch(3);
    }

    void Create()
    {
        _length = _maxSize;
        for (int i = 0; i < _maxSize; ++i)
        {
            _table[i] = i;
        }
    }
    
    int BSearch(int key) //二分查找,折半查找， 只适合有序表
    {
        int low = 0;
        int high = _length - 1;

        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (key == _table[mid])
                return mid;
            else if (key < _table[mid])
            {
                high = mid - 1;
            }
            else
            {
                low = mid + 1;
            }
        }
        return 0;
    }


    int _table[_maxSize];
    int _length = 0;

};

#endif //DATASTRUCTURE_BINARYSEARCH_H
