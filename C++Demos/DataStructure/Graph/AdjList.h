//
// Created by caichao on 2019-03-27.
//

#ifndef DATASTRUCTURE_ADJLIST_H
#define DATASTRUCTURE_ADJLIST_H

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <stack>

class AdjList
{

#define kMAX_VERTEX_NUM 20

    struct ArcNode{
        int info;
        int adjvertex;
        ArcNode *nextarc = NULL;
    };

    struct VNode{
        char data;
        ArcNode *firstarc = NULL;
    };

    enum GraphType{
        UG,
        DG
    };

public:

    static void Test()
    {
        AdjList list;
        list.Create(DG);
        list.FindArticul();
        list.TopologicalSort();
    }

    AdjList(){

    }

    int Locate(char v)
    {
        for (int i = 0; i < vexnum; ++i)
        {
            if (adjLis[i].data == v)
                return i;
        }
        throw std::invalid_argument("error");
    }

    void Create(GraphType type) //创建无向图
    {
        FILE *file = type == UG ? fopen("g2.txt","r") : fopen("g4.txt","r");
        printf("input vexnum,arcnum\n");
        fscanf(file,"%d%d",&vexnum,&arcnum);
        printf("input vex value");
        for (int i = 0; i < vexnum; ++i)
        {
            fscanf(file," %c",&adjLis[i].data);
        }

        printf("input arc value\n");
        for (int j = 0; j < arcnum; ++j)
        {
            char v1,v2;
            int info;
            fscanf(file," %c %c %d",&v1,&v2,&info);

            int iv1 = Locate(v1);
            int iv2 = Locate(v2);

            if (type == UG)
            {
                ArcNode *node = new ArcNode;
                node->info = info;
                node->adjvertex = iv1;
                node->nextarc = NULL;

                ArcNode *root = adjLis[iv2].firstarc;
                if (root)
                {
                    while (root->nextarc)
                        root = root->nextarc;
                    root->nextarc = node;
                }
                else
                {
                    adjLis[iv2].firstarc = node;
                }
            }
            

            ArcNode *node1 = new ArcNode;
            node1->info = info;
            node1->adjvertex = iv2;
            node1->nextarc = NULL;

            ArcNode *root = adjLis[iv1].firstarc;
            if (root)
            {
                while (root->nextarc)
                    root = root->nextarc;
                root->nextarc = node1;
            }
            else
            {
                adjLis[iv1].firstarc = node1;
            }
        }
        fclose(file);
    }

    void FindArticul() //求关节点
    {
        int count = 1;
        int visited[kMAX_VERTEX_NUM];
        int low[kMAX_VERTEX_NUM];
        for (int i = 0; i < kMAX_VERTEX_NUM; ++i)
        {
            visited[i] = -1;
            low[i] = -1;
        }

        visited[0] = count; //第一个访问的点
        ArcNode *p = adjLis[0].firstarc;
        int v = p->adjvertex; //第一个邻节点
        DFSArticul(v,visited,low,count); //从点v开始深度遍历
        if (count < vexnum) //并未访问到所有的点，那么v是一个关节点，这里是一个树根
        {
            printf("树根v:%c\n",adjLis[0].data);
            while (p->nextarc) //遍历树根的邻结点
            {
                p = p->nextarc;
                v = p->adjvertex;
                if (visited[v] < 0)
                    DFSArticul(v,visited,low,count);
            }
        }
    }

    void DFSArticul(int v,int visited[kMAX_VERTEX_NUM],int low[kMAX_VERTEX_NUM],int &count)
    {
        int min = ++count;
        visited[v] = min; //记录第v个点的
        printf("vis:%c\n",adjLis[v].data);
        for (ArcNode *p = adjLis[v].firstarc;p;p = p->nextarc) //遍历所有的领节点，找到最小的序号
        {
            int w = p->adjvertex; //邻结点，表示已v为尾，adjvex 为首 的弧
            if (visited[w] < 0) //还未访问点w,那么进行深度遍历
            {
                DFSArticul(w,visited,low,count); //深度遍历 w 的邻结点，可以求得 low[w]
                if (low[w] < min) //求最小的点，如果有回路，这里将得到一个小值
                {
                    min = low[w];
                }

                if (low[w] >= visited[v]) //关节点
                    printf("叶子v:%c\n",adjLis[v].data);
            }
            else if (visited[w] < min)
            {
                min = visited[w];
            }
        }
        low[v] = min; //求得访问点v所有邻结点的最小v
    }

    void TopologicalSort() //拓扑排序
    {
        int degrees[kMAX_VERTEX_NUM] = {0}; //自动初始化0

        FindInDegree(degrees); //计算入度

        std::stack<int> stack;
        std::stack<int> topologicalStack;
        int ve[kMAX_VERTEX_NUM] = {0}; //最早发生时间
        for (int i = 0; i < vexnum; ++i)
        {
            if (!degrees[i]) //入度为0的入栈
                stack.push(i);
        }

        int count = 0;
        printf("拓扑排序\n");
        while (!stack.empty())
        {
            int idx = stack.top();
            stack.pop();
            topologicalStack.push(idx);
            printf("v %c \n",adjLis[idx].data);
            ++count;
            for (ArcNode *p = adjLis[idx].firstarc; p ; p = p->nextarc) //对所有邻结点
            {
                if (!(--degrees[p->adjvertex])) //将邻结点入度 - 1
                    stack.push(p->adjvertex); //入度为0的点入栈
                if (ve[idx] + p->info > ve[p->adjvertex]) //跟新点p->adjv的最早发生时间，如果尾点的发生时间大于头点的最早发生时间
                    ve[p->adjvertex] = ve[idx] + p->info;
            }
        }

        if (count < vexnum)
            printf("graph has  circle\n");
        else
            printf("graph has no circle\n");

        CriticalPath(topologicalStack,ve);
    }

    void CriticalPath(std::stack<int> topological, int ve[kMAX_VERTEX_NUM])
    {
        printf("critical path \n");
        int vl[kMAX_VERTEX_NUM]; //在不印象活动的前提下，最晚的开始时间
        for (int i = 0; i < kMAX_VERTEX_NUM; ++i) //初始化，最迟发生时间为最早发生时间， 对最后一个点的发生时间必须是最早时间，
        {
            vl[i] = ve[i];
        }
        while (!topological.empty()) //求最迟发生时间
        {
            int idx = topological.top(); //取出拓扑排序最后一个点
            topological.pop();
            for (ArcNode *p = adjLis[idx].firstarc;p; p = p->nextarc) //遍历其临界点
            {
                int k = p->adjvertex;
                int dut = p->info;
                if (vl[k] - dut < vl[idx]) //计算最迟发生时间，头点的发生时间比尾的发生时间还短，那么缩短尾点的时间，过长导致其它点时间不够，所以要缩短
                    vl[idx] = vl[k] - dut;
            }
        }

        for (int j = 0; j < vexnum; ++j) //求关键活动 和 每个活动<i,j> 最早 最迟开始时间
        {
            for (ArcNode *p = adjLis[j].firstarc;p;p = p->nextarc)
            {
                int k = p->adjvertex;
                int dut = p->info;
                int ee = ve[j];
                int el = vl[k] - dut;
                char tag = el == ee ? '*' : ' ';
                printf("%c %c %d %d %d %c \n",adjLis[j].data,adjLis[k].data,dut,ee,el,tag);
            }
        }
    }

    void FindInDegree(int degree[kMAX_VERTEX_NUM])
    {
        for (int i = 0; i < vexnum; ++i)
        {
            ArcNode *node = adjLis[i].firstarc;
            while (node)
            {
                ++degree[node->adjvertex];
                node = node->nextarc;
            }
        }
    }

private:
    VNode adjLis[kMAX_VERTEX_NUM];
    int vexnum,arcnum;
    int kind;
};

#endif //DATASTRUCTURE_ADJLIST_H
