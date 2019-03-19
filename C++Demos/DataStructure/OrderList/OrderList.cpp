//
// Created by caichao on 2019-03-18.
//

#include "OrderList.h"
//
//OrderList::OrderList(int listSize) : listSize_(listSize)
//{
//
//}

void OrderList::Test()
{
  OrderList list(2);
  list.Insert(0,0);
  list.Insert(1,0);
  list.Insert(2,0);
  list.Insert(3,0);
  list.Insert(5,1);

  for (int i = 0; i < list.length_; ++i) {

    std::cout << "va : " << list.elems_[i] << " ";

  }
}

OrderList::OrderList(int listSize) {

  elems_ = (int*)malloc(listSize * sizeof(int));

}

void OrderList::Insert(int elem, int index) {

  if (index < 0 || index > length_) {
    return;
  }

  if (length_ >= listSize_)
  {
    elems_ = (int*)realloc(elems_,(listSize_ + IncrementSize) * sizeof(int));
    listSize_ += IncrementSize;
  }

  int *q = &elems_[index];
  for (int i = length_ ; i > index; --i)
  {
    elems_[i] = elems_[i - 1];
  }
  elems_[index] = elem;
  length_++;
}

void OrderList::Delete(int index) {

}




