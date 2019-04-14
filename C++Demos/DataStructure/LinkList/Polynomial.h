//
// Created by caichao on 2019-03-20.
//

#ifndef DATASTRUCTURE_POLYNOMIAL_H
#define DATASTRUCTURE_POLYNOMIAL_H

class Polynomial
{
public:

    static void Test();

    Polynomial();

    void AddNode(float param, int pow);

    Polynomial *operator + (const Polynomial &polynomial);

    void Traverse();

private:

    struct Node{
        float param = 0;
        int pow = 0;
        Node *next = nullptr;
    };

    Node *head_ = nullptr;
};

#endif //DATASTRUCTURE_POLYNOMIAL_H
