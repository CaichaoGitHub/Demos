//
// Created by caichao on 2019-03-19.
//

#ifndef DATASTRUCTURE_DULINKLIST_H
#define DATASTRUCTURE_DULINKLIST_H

class DuLinkList
{

    class Node;

public:

    static void Test();

    DuLinkList();

    void PushBack(int e);
    void PushFront(int e);
    void PopFront();
    void PopBack();

    Node* GetNodeAtNext(int index);

    void Insert(int e, int index);
    void Delete(int index);

    void Travse();

private:


    struct Node{

        int data;
        Node *next = nullptr;
        Node *prior = nullptr;

    };

    Node *head_ = nullptr;
    Node *tail_ = nullptr;
};

#endif //DATASTRUCTURE_DULINKLIST_H
