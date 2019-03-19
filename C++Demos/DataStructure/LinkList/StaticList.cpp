//
// Created by caichao on 2019-03-18.
//

#include "StaticList.h"
#include <stdio.h>

void StaticList::Test() {

  StaticList s;

  s.Insert(0,0);
  s.Insert(1,0);
  s.Insert(2,0);
  s.Insert(3,0);
  s.Traverse();
  s.Delete(2);
  s.Delete(1);
  s.Traverse();

}

StaticList::StaticList() {

  //考虑将head节点作为空节点，并保持第一个节点作为索引节点，
  //尾部第一个节点作为插入节点
  for (int i = 0; i < 100; ++i) {
    Node &node = list_[i];
    if(i < 99)
    {
      node.cur = i+1;
    }
  }

  list_[99].cur = 0;
  list_[98].cur = 0; //作为分割节点，不至于把最后一个节点作为empty节点分配了

}

int StaticList::GetLength() {

  int i = list_[99].cur;
  int j = 0;
  while (i)
  {
    j++;
    i = list_[i].cur;
  }
  return j;

}

void StaticList::Insert(int e, int index) {

  if(index <= GetLength())
  {
    int j = GetEmptyNode(); //得到空节点
    int k = 99; //从末尾开始遍历
    if (j)
    {
      for (int i = 0; i < index; ++i) //找到插入点
      {
        k = list_[k].cur;
      }

      list_[j].elem = e;
      list_[j].cur = list_[k].cur;
      list_[k].cur = j;
    }
  }
}

void StaticList::Delete(int index) {

  if(index < GetLength())
  {
    int k = 99;
    for (int i = 0; i < index; ++i)
    {
      k = list_[k].cur;
    }

    int j = list_[k].cur;
    list_[k].cur = list_[j].cur;
    SaveEmptyNode(j);
  }

}


int StaticList::GetEmptyNode() {

  int i = list_[0].cur;
  if(i)
    list_[0].cur = list_[i].cur;

  return i;
}


void StaticList::SaveEmptyNode( int &index) {

  list_[index].cur = list_[0].cur;
  list_[0].cur = index;

}

void StaticList::Traverse() {

  printf("\n");
  int j = 99;
  while (list_[j].cur)
  {
    j = list_[j].cur;
    printf("%d",list_[j].elem);
  }
  printf("\n");

}










