//
// Created by caichao on 2019-03-18.
//

#ifndef DATASTRUCTURE_ORDERLIST_H
#define DATASTRUCTURE_ORDERLIST_H

#include <iostream>

//template <typename T>
class OrderList {

 public:

  static void Test();

 public:

  OrderList(int listSize);

  //random access any elements are fast ,
  void Insert(int elem, int index); //insert or delete will cost a lot of time at moving elements
  void Delete(int index);

 private:

  const static int IncrementSize = 4;

  int *elems_ = nullptr;
  int length_ = 0;
  int listSize_ = 0;

};




#endif //DATASTRUCTURE_ORDERLIST_H
