//
// Created by caichao on 2019-03-24.
//

#ifndef DATASTRUCTURE_BITREE_H
#define DATASTRUCTURE_BITREE_H
#include <string>
#include <iostream>
#include <stack>

class Bitree
{
    struct Node;
public:

    static void Test(){
        Bitree bitree;
        bitree.Create(bitree.root);
        bitree.LogPreOrder(bitree.root);
        printf("\n");
        bitree.LogMidOrder(bitree.root);
        printf("\n");
        bitree.LogPreOrder2(bitree.root);
        printf("\n");
        bitree.InOrderTraverse(bitree.root);
    }

    Bitree(){
        std::cout << "输入节点信息 空字符表示空节点，" << std::endl;
        root = NULL;

    }
    Bitree(std::string string){

        if (string.length())
        {
//            if ()
        }

    }

    void Create(Node* &node)
    {
        std::cout << "enter ch q or space means null ptr" << std::endl;
        char ch[2] ;
//        scanf("%s",ch);
        gets(ch);
        fflush(stdin);

        if (ch[0] == 'q' || ch[0] ==' ')
        {
            node = nullptr;
            std::cout << "empty ptr" << std::endl;
        }
        else
        {
            node = (Node*)malloc(sizeof(Node));
            node->data = ch[0];
            std::cout << "create left ptr" << std::endl;
            Create(node->left);
            std::cout << "create right ptr" << std::endl;
            Create(node->right);
        }

    }

    std::string Create(std::string string,Node *& node)
    {
        if (string.length())
        {
            if (string.at(0) == ' ')
            {
                node = nullptr;
                string = string.substr(1);
            }
            else
            {
                node = (Node*)malloc(sizeof(Node));
                node->data = string.at(0);
                std::string str = Create(string.substr(1),node->left);
                string = Create(str,node->right);
            }
        }
        else
        {
            node = nullptr;
        }
        return string;
    }

    void LogPreOrder(Node *node)
    {
        if (node)
        {
            printf("%c ",node->data);
            LogPreOrder(node->left);
            LogPreOrder(node->right);
        }
        else
            printf("null ");
    }

    void LogMidOrder(Node *node)
    {
        if(node)
        {
            LogMidOrder(node->left);
            printf("%c ",node->data);
            LogMidOrder(node->right);
        }
//        else
//            printf("null ");
    }

    void LogPreOrder2(Node* node)
    {
        std::stack<Node*> stack;
        stack.push(node);
        while (!stack.empty())
        {
            node = stack.top();
            stack.pop();

            while (node)
            {
                printf("%c ",node->data);
                if (node->right)
                    stack.push(node->right);
                node = node->left;
            }
            printf("null ");

//            while (node->left)
//            {
//                if ()
//
//                printf("%c ")
//            }
        }


    }

    void InOrderTraverse(Node *node)
    {
        std::stack<Node*> stack;
        stack.push(node);
        Node *p = stack.top();
        while (!stack.empty() || p)
        {
            while (p) //对于输入节点，如果节点存在，向左入栈，
            {
                if (p->left)
                    stack.push(p->left);
//                else
//                    printf("null ");
                p = p->left;
            }

            if (!stack.empty())
            {
                auto p = stack.top(); //弹出一个栈顶节点，打印节点
                stack.pop();
                printf("%c ",p->data);
                if (p->right) //尝试向右走1步
                    stack.push(p->right);
//                else
//                    printf("null ");
                p = p->right;
            }
        }
    }

private:
    struct Node{
        char data;
        Node *left;
        Node *right;
        Node *parent;
    };

    Node *root = nullptr;
};

#endif //DATASTRUCTURE_BITREE_H






