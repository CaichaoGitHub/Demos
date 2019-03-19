//
// Created by caichao on 2019-03-19.
//

#ifndef DATASTRUCTURE_DULINKLIST_H
#define DATASTRUCTURE_DULINKLIST_H

class DuLinkList
{

public:
    DuLinkList();

    virtual void Test() = 0;

private:


    struct Node{

        int data;
        Node *next;
        Node *prior;

    };

    Node *root_ = nullptr;
};

class DuT : public DuLinkList
{
public:

};

#endif //DATASTRUCTURE_DULINKLIST_H
