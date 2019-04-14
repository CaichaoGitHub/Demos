//
// Created by caichao on 2019-03-30.
//

#ifndef DATASTRUCTURE_ADJMULTILIST_H
#define DATASTRUCTURE_ADJMULTILIST_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <queue>

//针对无向图
class AdjMultiList
{
public:

    static void Test()
    {
        AdjMultiList list;
        list.Create();
        list.Traverse();

        CSTree  tree = NULL;
        list.DFSForest(tree);
        list.MiniSpanTree_PRIM();
    }

#define kMax_VERTEX_NUM 20
    typedef enum{unvisited,visited} VisitIf;
    struct EBox{
        VisitIf mark = unvisited;
        int weight = 0;
        int ivex = 0; // edge v1
        int jvex = 0; //edge v2
        EBox *ilink = nullptr;//link rely on ivex
        EBox *jlink = nullptr;//link repy on jvex
    };

    struct VexBox{
        int data; //vex value
        EBox *firstEdge; //first edge reply on cur vex
    };

    VexBox adjMuli[kMax_VERTEX_NUM];
    int vexnum = 0;
    int edgenum = 0;

    typedef struct CSNode{
        int data;
        CSNode *firstchild = nullptr,*nextsibling = nullptr;
    }*CSTree;

    AdjMultiList(){}

    void Create(){

        FILE *file = fopen("g1.txt","r");
        printf("input ver,edge \n");
        fscanf(file,"%d%d",&vexnum,&edgenum);


        for (int i = 0; i < vexnum; ++i)
        {
            printf("input ver value1 \n");
            fscanf(file,"%d",&adjMuli[i].data);
            adjMuli[i].firstEdge = nullptr;
        }

        for (int jj = 0; jj < edgenum; ++jj)
        {
            printf("input arc value1 value2 weight \n");
            int v1,v2,v3;
            fscanf(file,"%d%d%d",&v1,&v2,&v3);
            int i = Locate(v1);int j = Locate(v2);

            EBox *box = (EBox*)malloc(sizeof(EBox));
            box->ivex = i;
            box->jvex = j;
            box->weight = v3;

            box->ilink = adjMuli[i].firstEdge;
            adjMuli[i].firstEdge = box;

            box->jlink = adjMuli[j].firstEdge;
            adjMuli[j].firstEdge = box;

        }

        fclose(file);

    }

    //广度优先遍历
    void Traverse()
    {
        bool visited[kMax_VERTEX_NUM] = {0};
        std::queue<int> queue;
        for (int i = 0; i < vexnum; ++i)
        {
            if (!visited[i])
            {
                visited[i] = true;
                printf("%d\n",adjMuli[i].data);
                queue.push(i);
                while (!queue.empty())
                {
                    int v = queue.front() ;queue.pop();
                    for (int w = FirsAdj(v); w >= 0 ; w = NextAdj(v,w)) //遍历当前定点的邻接点，
                    {
                        if (!visited[w])
                        {
                            visited[w] = true;
                            printf("%d\n",adjMuli[w].data);
                            queue.push(w);
                        }
                    }
                }
            }
        }
    }

    int FirsAdj(int v)
    {
        if (adjMuli[v].firstEdge)
            return adjMuli[v].firstEdge->jvex;
        return -1;
    }

    int NextAdj(int v, int w)
    {
        EBox *root = adjMuli[v].firstEdge;
        while (root)
        {
            if (root->jvex == w)
            {
                if (root->ilink)
                    return root->ilink->jvex;
                return -1;
            }
            else
                root = root->ilink;
        }
        return -1;
    }

    void DFSTree(int v,CSTree &tree,bool visited[kMax_VERTEX_NUM])
    {
        visited[v] = true;
        CSNode *q = tree;
        for (int w = FirsAdj(v); w >= 0 ; w = NextAdj(v,w)) //广度优先遍历
        {
            if (!visited[w])
            {
                CSNode *node = (CSNode*)malloc(sizeof(CSNode));
                node->firstchild = nullptr;
                node->nextsibling = nullptr;
                node->data = adjMuli[w].data;

                if (!tree->firstchild)
                    tree->firstchild = node;
                else
                {
                    q->nextsibling = node;
                }
                q = node;
                DFSTree(w,node,visited);
            }
        }
    }

    void DFSForest(CSTree &tree)
    {
        bool visited[kMax_VERTEX_NUM] = {false};
        CSNode *q = tree;
        for (int i = 0; i < vexnum; ++i) //遍历所有节点
        {
            if (!visited[i]) //将未访问的节点作为根节点，准备创建一个科树
            {
                CSNode *node = (CSNode*)malloc(sizeof(CSNode));
                node->data = adjMuli[i].data;
                node->firstchild = nullptr;
                node->nextsibling = nullptr;

                if (!tree) //创建根节点
                    tree = node;
                else
                    q->nextsibling = node; //将根节点创建为兄弟节点
                q = node;
                DFSTree(i,node,visited); //对当前节点创建一颗广度树
            }
        }
    }

    void MiniSpanTree_KLSKR() //克鲁斯卡尔算法求最小生成树
    {

    }

    void MiniSpanTree_PRIM() //普里姆算法求最小生成树
    {
        std::cout<<"input start v value" << std::endl;
        int v;
        std::cin >> v;

        struct {
            int v = -1;
            int lowCost = INT_MAX;
        }closeEdge[kMax_VERTEX_NUM]; //当前集合中，v 到数组索引v的最短路径

        auto mininum = [&closeEdge,this]()->int{ //求最端路径的定点

            int k = -1;
            for (int i = 0; i < vexnum; ++i)
            {
                if (closeEdge[i].lowCost > 0 && closeEdge[i].v >= 0)
                {
                    if (k < 0)
                        k = i;
                    else
                    {
                        if (closeEdge[i].lowCost < closeEdge[k].lowCost)
                        {
                            k = i;
                        }
                    }
                }
            }
            return k;
        };

        int iv = Locate(v);
        closeEdge[iv].lowCost = 0;

        EBox *edge = adjMuli[iv].firstEdge;
        while (edge)
        {
            if (edge->ivex == iv) //iv -> jvex
            {
                closeEdge[edge->jvex].lowCost = edge->weight; //low cost
                closeEdge[edge->jvex].v = iv; //from iv
                edge = edge->ilink;
            }
            else
            {
                closeEdge[edge->ivex].lowCost = edge->weight; //low cost
                closeEdge[edge->ivex].v = iv; //from iv
                edge = edge->jlink;
            }
        }

        for (int i = 0; i < vexnum; ++i) //无向图边没有方向
        {
            int k = mininum(); //chose a lowcost point from group, means low edge

            if (k < 0 )
                break;
            printf("vexbe:%d vexend:%d cost:%d \n",adjMuli[closeEdge[k].v].data,adjMuli[k].data,closeEdge[k].lowCost);
            closeEdge[k].lowCost = 0;

            EBox *edge = adjMuli[k].firstEdge;
            while (edge) //更新 closeedge ,以最新加入集合的k点，求他的近点并加入closeEdge 数组
            {
                if (edge->ivex == k)
                {
                    if(closeEdge[edge->jvex].lowCost > edge->weight)
                    {
                        closeEdge[edge->jvex].lowCost = edge->weight;
                        closeEdge[edge->jvex].v = k; //to edge->jvex low cost is xx ,and is from k
                    }
                    edge = edge->ilink;
                }
                else
                {
                    if(closeEdge[edge->ivex].lowCost > edge->weight)
                    {
                        closeEdge[edge->ivex].lowCost = edge->weight;
                        closeEdge[edge->ivex].v = k;
                    }
                    edge = edge->jlink;
                }
            }
        }


    }

    int Locate(int v)
    {
        for (int i = 0; i < vexnum; ++i)
        {
            if (adjMuli[i].data == v)
                return i;
        }
        throw std::invalid_argument("error");
    }

};

#endif //DATASTRUCTURE_ADJMULTILIST_H












