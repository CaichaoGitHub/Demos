//
// Created by caichao on 2019-03-29.
//

#ifndef DATASTRUCTURE_ORTHLIST_H
#define DATASTRUCTURE_ORTHLIST_H

#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <iostream>

//针对有向图
class OrthList
{
#define kMax_vertex_count 20
public:

    static void Test()
    {
        OrthList list;
        list.Create();

        int finish[kMax_vertex_count] = {-1};
        list.DFSTraverse(finish);
        list.StrongConnected(finish);
    }

    struct ArcBox{
        int tailvex,headvex;
        ArcBox *hlink = nullptr,*tlink = nullptr;
    };

    struct VexNode{
        int data;
        ArcBox *firstin = nullptr,*firstout = nullptr;
    };

    VexNode vexList[kMax_vertex_count];
    int vexnum = 0;
    int arcnum = 0;

    void Create()
    {
        std::cout << "input ver and arc" <<std::endl;
        scanf("%d%d",&vexnum,&arcnum);
        for (int i = 0; i < vexnum; ++i)
        {
            std::cout << "input vertex v1" << std::endl;
            scanf("%d",&vexList[i].data);
        }


        for (int j = 0; j < arcnum; ++j)
        {
            std::cout << "input arc v1, v2" << std::endl;
            int v1;int v2;
            scanf("%d%d",&v1,&v2);

            int l1 = Locate(v1);
            int l2 = Locate(v2);

            ArcBox *p = (ArcBox*)malloc(sizeof(ArcBox));
            p->tailvex = l1;
            p->headvex = l2;

            p->hlink = vexList[l2].firstin; //将新的定点头尾指向，相应定点的出点和入点
            p->tlink = vexList[l1].firstout;

            //将首位指针指向新的定点
            vexList[l1].firstout = vexList[l2].firstin = p;
        }
    }

    int Locate(int v)
    {
        for (int i = 0; i < vexnum; ++i)
        {
            if (vexList[i].data == v)
                return i;
        }
        throw std::invalid_argument("error");
    }

    void DFSTraverse(int finish[kMax_vertex_count])
    {
        bool visited[kMax_vertex_count] = {false};
        int count = 0;
        for (int i = 0; i < vexnum; ++i)
        {
            if (!visited[i])
            {
                printf("tree:\n");
                DFS(i,visited,finish,count);
            }
        }
        printf("\n");
    }

    void DFS(int v, bool visited[kMax_vertex_count], int finish[kMax_vertex_count],int &count)
    {
        visited[v] = true;
        printf("v:%d ",vexList[v].data);
        finish[count++] = v;
        for (int w = FirstAdj(v); w >= 0; w = NextAdj(v,w))
        {
            if (!visited[w])
            {
                DFS(w,visited,finish,count);
            }

        }
    }

    int FirstAdj(int v)
    {
        VexNode node = vexList[v];
        if (node.firstout)
            return node.firstout->headvex;
        return -1;
    }

    int NextAdj(int v,int w)
    {
        ArcBox *node = vexList[v].firstout;
        while (node)
        {
            if (node->headvex == w)
            {
                if (node->tlink)
                    return node->tlink->headvex;
                break;
            }
            else
            {
                node = node->tlink;
            }
        }
        return -1;
    }

    void StrongConnected(int finish[kMax_vertex_count])
    {
        bool visited[kMax_vertex_count] = {false};
        int finished[kMax_vertex_count] = {-1};
        int count = 0;
        for (int i = vexnum-1; i > 0 ; --i) //逆序遍历
        {
            int vi = finish[i];
            if (!visited[vi])
            {
                printf("\nrever-tree\n");
                DFS(vi,visited,finished,count);
            }
        }
        printf("\n");
    }

};

#endif //DATASTRUCTURE_ORTHLIST_H
