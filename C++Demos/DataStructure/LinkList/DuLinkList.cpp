//
// Created by caichao on 2019-03-19.
//

#include "DuLinkList.h"
#include <stdlib.h>
#include <stdio.h>

void DuLinkList::Test()
{
    DuLinkList list;

    list.PushFront(2);
    list.Travse();
    list.PushFront(3);
    list.Travse();
    list.PushBack(4);
    list.Travse();
    list.Insert(5,1);
    list.Travse();
    list.PopBack();
    list.Travse();
}

DuLinkList::DuLinkList()
{
    head_ = (Node*)malloc(sizeof(Node));
    tail_ = (Node*)malloc(sizeof(Node));

    head_->next = tail_;
    head_->prior = nullptr;
    tail_->prior = head_;
    tail_->next = nullptr;
}

void DuLinkList::PushBack(int e)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = e;

    node->prior = tail_->prior;
    node->next = tail_;
    tail_->prior->next = node;
    tail_->prior = node;
}

void DuLinkList::PushFront(int e)
{
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = e;

    node->next = head_->next;
    node->prior = head_;
    head_->next->prior = node;
    head_->next = node;

}

void DuLinkList::PopFront()
{

}

void DuLinkList::PopBack()
{
    if (tail_->prior != head_)
    {
        Node *deleteNode = tail_->prior;
        deleteNode->prior->next = tail_;
        tail_->prior = deleteNode->prior;
        free(deleteNode);
    }
}

DuLinkList::Node* DuLinkList::GetNodeAtNext(int index)
{
    int cntIndex = 0;
    Node *firstNode = head_->next;
    while (firstNode != tail_)
    {
        if(cntIndex == index)
        {
            break;
        }
        else
        {
            ++cntIndex;
        }
    }

    if (cntIndex == index)
        return firstNode;

    return nullptr;
}

void DuLinkList::Insert(int e, int index)
{
    Node* node = GetNodeAtNext(index);
    if (node)
    {
        Node *newNode = (Node*)malloc(sizeof(Node*));
        newNode->data = e;

        node->prior->next = newNode;
        newNode->next = node;
        newNode->prior = node->prior;
        node->prior = newNode;
    }
}

void DuLinkList::Delete(int index)
{

}

void DuLinkList::Travse()
{
    printf("\n");
    Node *node = head_->next;
    while (node != tail_)
    {
        printf("%d ",node->data);
        node = node->next;
    }
    printf("\n");
}
