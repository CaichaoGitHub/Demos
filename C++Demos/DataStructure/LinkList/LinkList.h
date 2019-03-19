//
// Created by caichao on 2019-03-18.
//

#ifndef DATASTRUCTURE_LINKLIST_H
#define DATASTRUCTURE_LINKLIST_H

class LinkList {

 public:

  static void Test();

  virtual ~LinkList();
  LinkList();
  const int &GetElemment(int index);
  void Insert(int element,int index);
  void Delete(int element,int index);


 private:

  struct Node{

   int elem;
   Node *next = nullptr;
   Node *pre = nullptr;

 };

  Node *root_ = nullptr;
  int length_ = 0;

};

#endif //DATASTRUCTURE_LINKLIST_H
