//
// Created by caichao on 2019-03-20.
//

#include "Polynomial.h"
#include <iostream>

void Polynomial::Test()
{
    Polynomial pa;
    pa.AddNode(1,1);

    pa.AddNode(3,2);
    pa.AddNode(4,3);
    pa.AddNode(5,10);

    pa.Traverse();

    Polynomial pb;
    pb.AddNode(1,1);

    pb.AddNode(4,3);

    pb.Traverse();

    Polynomial *pn = pa + pb;

    pa.Traverse();
    pb.Traverse();

}

Polynomial::Polynomial()
{
    head_ = new Node;
    head_->next = 0;
    head_->param = 0;
    head_->next = 0;
}

Polynomial* Polynomial::operator+(const Polynomial &polynomial)
{
    Node *aNode = this->head_->next;
    Node *bNode = polynomial.head_->next;

    Node *newHead = new Node;
    newHead->next = nullptr;
    Node *tail = newHead;
    while (aNode && bNode)
    {
        if (aNode->pow == bNode->pow)
        {
            aNode->param += bNode->param;
            if (aNode->param != 0){
                tail->next = aNode;
                tail = aNode;
                aNode = aNode->next;
            }
            else
            {
                Node *tmp = aNode;
                aNode = aNode->next;
                delete tmp;
            }
            Node *tmp = bNode;
            bNode = bNode->next;
            delete tmp;
        }
        else if (aNode->pow > bNode->pow)
        {
            tail->next = bNode;
            tail = bNode;
            bNode = bNode->next;
        }
        else
        {
            tail->next = aNode;
            tail = aNode;
            aNode = aNode->next;
        }
    }

    if (aNode)
    {
        tail->next = aNode;
    }

    if (bNode)
    {
        tail->next = bNode;
    }

    delete head_;
    head_ = newHead;
    polynomial.head_->next = nullptr;
}

void Polynomial::AddNode(float param, int pow)
{
    Node *node = new Node;
    node->param = param;
    node->pow = pow;
    node->next = nullptr;

    Node *tail = head_;
    while (tail->next)
    {
        tail = tail->next;
    }

    node->next = nullptr;
    tail->next = node;

}

void Polynomial::Traverse()
{
    std::cout << std::endl;
    Node *node = head_->next;
    while (node)
    {
        std::cout << "param:" << node->param << " pow:" << node->pow << " + ";
        node = node->next;
    }
    std::cout << std::endl;
}






