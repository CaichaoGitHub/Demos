//
// Created by caichao on 2019-03-18.
//

#include "LinkList.h"
#include <iostream>
void LinkList::Test()
{
  LinkList list;
  list.Insert(1,0);
  list.Insert(6,0);
  list.Insert(12,0);
  list.Insert(14,0);
  list.Insert(2,0);
  list.Insert(3,1);
  list.Insert(4,4);

  printf("\n");
  Node *node = list.root_;
  while (node)
  {
    std::cout << "v:" << node->elem << " ";
    node = node->next;
  }
}

LinkList::~LinkList() {

  Node *node = root_;
  while (node)
  {
    Node *deleteNode = node;
    node = node->next;
    delete deleteNode;
  }

}

LinkList::LinkList()
{

}

void LinkList::Delete(int element, int index)
{

}

void LinkList::Insert(int element, int index)
{
  if(index <= length_&& index >= 0)
  {
    Node *newNode = new Node;
    newNode->elem = element;

    Node *insertNode = root_;
    Node *insertPreNode = nullptr;
    for (int i = 0; i < index; ++i) {
      if(insertNode)
      {
        insertPreNode = insertNode;
        insertNode = insertNode->next;
      }
    }

    if(insertNode)
    {
      newNode->next = insertNode;
      if (insertPreNode)
        insertPreNode->next = newNode;
      else
        root_ = newNode;
    }
    else
    {
      if (root_)
      {
        insertPreNode->next = newNode;
      }
      else
      {
        root_ = newNode;
      }

    }

    ++length_;
  }
}

const int& LinkList::GetElemment(int index)
{

}









