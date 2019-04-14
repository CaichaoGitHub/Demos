//
// Created by caichao on 2019-03-24.
//

#ifndef DATASTRUCTURE_GLIST_H
#define DATASTRUCTURE_GLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <regex>
#include <iostream>

class GList
{
    struct Node;
public:

    static void Test()
    {
        Node *c = (Node*)malloc(sizeof(Node));
        c->tag = ElemTag::list;

        c->ptr.hp = (Node*)malloc(sizeof(Node));
        c->ptr.hp->tag = ElemTag::atom;
        c->ptr.hp->data = 'a';

        c->ptr.tp = (Node*)malloc(sizeof(Node));
        c->ptr.tp->tag = ElemTag::list;

        c->ptr.tp->ptr.hp = (Node*)malloc(sizeof(Node));
        c->ptr.tp->ptr.hp->tag = ElemTag::list;
        c->ptr.tp->ptr.tp = nullptr;

        c->ptr.tp->ptr.hp->ptr.hp = (Node*)malloc(sizeof(Node));
        c->ptr.tp->ptr.hp->ptr.hp->tag = ElemTag::atom;
        c->ptr.tp->ptr.hp->ptr.hp->data = 'b';
        c->ptr.tp->ptr.hp->ptr.tp = nullptr;

        int depth = GetDepth(c);
        if (depth)
        {

        }

        Node *copyNode = nullptr;
        CopyList(c,copyNode);
        if (copyNode)
        {}

        std::string str= "((a),(b,c,d))";
        Node *node1;
        CreateList(node1,str);

        if(node1)
        {}
    }

    GList(){



    }

    static int CreateList(Node *& node,std::string string)
    {
        if (string == "()" || string.length() == 0)
            node = nullptr;
        else
        {
            node = (Node*)malloc(sizeof(Node));
            if (string.length() == 1) //原子节点
            {
                node->tag = ElemTag::atom;
                node->data = *string.c_str();
            }
            else //连表节点
            {
                node->tag = ElemTag::list;
                string = string.substr(1,string.length() - 2);
                Node *nnode = node;
                if(!string.empty()) //处理同级连表
                {
                    do
                    {
                        std::string bstring;
                        Server(string,bstring);
                        CreateList(nnode->ptr.hp,bstring); //表头
                        //链接表尾
                        if (!string.empty())
                        {
                            nnode->ptr.tp = (Node*)malloc(sizeof(Node));
                            nnode->ptr.tp->tag = ElemTag ::list;
                            nnode = nnode->ptr.tp;
                        }
                    }
                    while (!string.empty());
                    nnode->ptr.tp = nullptr;
                }
            }
        }
    }

    static void Server(std::string &astring,std::string &bstring)
    {
//        astring = "(b,c,d)";
        //
        std::regex regex("^(\\(.*?\\)),?(.*)|(.*?),(.*?)");
//        std::regex regex("(.*?,).*");
        std::smatch match;
        std::regex_match(astring,match,regex);
        std::cout << match.size() << std::endl;
//        for (int i = 0; i < match.size(); ++i)
//        {
//            std::cout << match[i].str() << std::endl;
//        }
        if (match.size() == 5)
        {
            if (match[1].length())
            {
                bstring = match[1].str();
                astring = match[2].str();
            }
            else if (match[3].str().length())
            {
                bstring = match[3].str();
                astring = match[4].str();
            }
        }
        else
        {
            bstring = astring;
            astring = "";
        }
    }

    static int CopyList(Node *node,Node *&targetNode)
    {
        //recursive copy
        if (!node)
        {
            targetNode = nullptr;
            return 0;
        }

        targetNode = (Node*)malloc(sizeof(Node));
        targetNode->tag = node->tag;
        if (node->tag == ElemTag::atom)
            targetNode->data = node->data;
        else
        {
            CopyList(node->ptr.hp,targetNode->ptr.hp);
            CopyList(node->ptr.tp,targetNode->ptr.tp);
        }
    }

    static int GetDepth(Node *node)
    {
        if (!node)
            return 1;
        if (node->tag == ElemTag::atom)
            return 0;

        //hp 指向头节点，tp指向尾部节点，
        //利用tp进行横向搜索
        //李勇hp进行纵向搜索
        int maxdepth = 0;
        for (Node *nn = node; nn ; nn = nn->ptr.tp)
        {
            int tmp = GetDepth(nn->ptr.hp);
            if (tmp > maxdepth)
                maxdepth = tmp;
        }
        return maxdepth + 1;
    }

private:
    enum class ElemTag{
        atom,
        list
    };
    struct Node{
        ElemTag tag;
        union {
            char data;
            struct {
                Node *hp = nullptr;
                Node *tp = nullptr;
            } ptr;
        };
    };

};

#endif //DATASTRUCTURE_GLIST_H








