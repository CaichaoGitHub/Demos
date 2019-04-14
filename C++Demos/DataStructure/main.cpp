#include <iostream>
#include "OrderList/OrderList.h"
#include "LinkList/LinkList.h"
#include "LinkList/StaticList.h"
#include "LinkList/DuLinkList.h"
#include "LinkList/Polynomial.h"
#include "stack&queue/ArrayStack.h"
#include "stack&queue/Maze.h"
#include "stack&queue/Hanoi.h"
#include "stack&queue/LinkQueue.h"
#include "string/String.h"
#include "Array/SparseMatrix.h"
#include "Array/CrossList.h"
#include "Array/GList.h"
#include "tree/Bitree.h"
#include "tree/HuffmanTree.h"
#include "Graph/AdjMatrix.h"
#include "Graph/AdjMultiList.h"
#include "Graph/OrthList.h"
#include "Graph/AdjList.h"
#include "Search/BinarySearch.h"
#include "Search/StaticSearchTree.h"
#include "Search/BinarySortTree.h"
#include "Search/BalancedBinaryTree.h"
#include "Search/BTree.h"
#include "Sort/InsertionSort.h"
#include "Sort/QuickSort.h"
#include "Sort/Radixsort.h"


void TestPointRef()
{
    int *p = new int(2);
    int *&pRef = p;
    pRef = new int(4);

    if (p)
    {

    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
//
//    OrderList::Test();
//    LinkList::Test();
//    StaticList::Test();
//    DuLinkList::Test();
//    Polynomial::Test();
//    ArrayStack<int>::Test2();
//    ArrayStack<int>::Test();

//    Maze::Test();

//    Hanoi::Test();

//    LinkQueue<int>::Test();
//    String::Test();

//    SparseMatrix::Test();
//    CrossList::Test();

//    GList::Test();
//    Bitree::Test();
//    HuffmanTree::Test();
//    AdjMatrix::Test();
//    AdjMultiList::Test();

//    OrthList::Test();

//    AdjList::Test();

//    BinarySearch::Test();
//    StaticSearchTree::Test();

//    BinarySortTree::Test();
//    TestPointRef();
//    BalancedBinaryTree::Test();
//    BTree::Test();
//    InsertionSort::Test();

//    QuickSort::Test();

    Radixsort::Test();

    return 0;
}