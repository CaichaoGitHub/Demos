//
// Created by caichao on 2019-03-23.
//

#ifndef DATASTRUCTURE_LINKQUEUE_H
#define DATASTRUCTURE_LINKQUEUE_H
#include <iostream>

template <typename T>
class LinkQueue
{
public:

    static void Test()
    {
        LinkQueue<int> queue;
        queue.Enqueue(2);
//        queue.Enqueue(3);
        queue.Enqueue(4);
        queue.Travel();
        queue.Dequeue();
        queue.Dequeue();
        queue.Travel();
        queue.Enqueue(2);
        queue.Enqueue(3);
        queue.Travel();

        //银行客户时间模拟
    }

    LinkQueue(){
        head = new QNode;
        tail = head;
    }

    void Enqueue(T data)
    {
        QNode *node = new QNode;
        node->data = data;
        node->next = nullptr;
        tail->next = node;
        tail = node;
    }

    T Dequeue()
    {
        if (head->next)
        {
            QNode *node = head->next;
            if (node == tail)
            {
                head->next = nullptr;
                tail = head;
            }
            else
            {
                head->next = node->next;
            }
            T data = node->data;
            delete node;
            return data;
        }
    }

    void Travel()
    {
        std::cout << "队头 ";
        QNode *node = head->next;
        while (node)
        {
            std::cout << node->data << " ";
            node = node->next;
        }
        std::cout << "队尾" <<std::endl;
    }

private:
    struct QNode{
        T data;
        QNode *next = nullptr;
    };

    QNode *head = nullptr;
    QNode *tail = nullptr;

};

#endif //DATASTRUCTURE_LINKQUEUE_H
