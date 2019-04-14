//
// Created by caichao on 2019-03-27.
//

#ifndef DATASTRUCTURE_ADJMATRIX_H
#define DATASTRUCTURE_ADJMATRIX_H

//#include <stdlib.h>
//#include <stdio.h>
#include <iostream>

class AdjMatrix
{
    typedef enum {
        DG,DN,UDG,UDN
    }GraphKind;

    struct ArcCell{
        int adj;
        void *info;
    };

public:

    static void Test(){
        AdjMatrix matrix1;
        matrix1.CreateUDG();
        matrix1.Log();
        matrix1.DFSTraverse();
    }

    AdjMatrix(){}

    void CreateUDG(){

        std::cout << "输入定点和弧数量" << std::endl;
        scanf("%d%d",&vexnum,&arcnum);
        std::cout << "输入所有定点" << std::endl;
        for (int i = 0; i < vexnum; ++i)
        {
            scanf("%d",&vexs[i]); //init vertex
        }

        std::cout << "输入弧的尾部和头部以及权重" << std::endl;
        for (int j = 0; j < arcnum; ++j) //依次输入弧信息
        {
            int v1,v2,w;
            scanf("%d%d%d",&v1,&v2,&w);
            int iv1 = Locate(v1); //基于定点，获取在图的存储索引
            int iv2 = Locate(v2);
            matrix[iv1][iv2].adj = w; //存储信息
            matrix[iv2][iv1].adj = w;
        }
    }

    int Locate(int v)
    {
        for (int i = 0; i < vexnum; ++i)
        {
            if (vexs[i] == v)
                return i;
        }
        throw std::invalid_argument("invalild vertex value");
    }

    void Log()
    {
        std::cout << std::endl;
        std::cout << "  ";
        for (int i = 0; i < vexnum; ++i)
        {
            std::cout << vexs[i] << " ";
        }

        std::cout << std::endl;
        for (int j = 0; j < vexnum; ++j)
        {
            std::cout << vexs[j] << " ";
            for (int i = 0; i < vexnum; ++i)
            {
                std::cout << matrix[i][j].adj << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void DFSTraverse()
    {
        bool visited[20] = {false};
        for (int i = 0; i < vexnum; ++i)
        {
            if (!visited[i])
                DFS(i,visited);
        }
    }

    void DFS(int v,bool visited[20])
    {
        visited[v] = true;
        printf("v:%d",vexs[v]);
        fflush(stdout);
        int w = 0;
        do{
            w = NextAdj(v,w);
            if (w < 0)
                break;
            if (!visited[w])
                DFS(w,visited);
            w++;
        }while (1);
    }


    int NextAdj(int v,int w)
    {
        for (int i = w; i < vexnum; ++i)
        {
            if (matrix[v][i].adj != 0)
            {
                return i;
            }
        }
        return -1;
    }


    void ShortestPath_DIJ(int v0)
    {
        bool P[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
        bool final[MAX_VERTEX_NUM];
        int D[MAX_VERTEX_NUM];
        for (int i = 0; i < vexnum; ++i)
        {
            final[i] = false;
            D[i] = matrix[v0][i].adj;
            for (int j = 0; j < vexnum; ++j)
            {
                P[i][j] = false;
            }

            if (D[i] < INFINITY)
            {
                P[i][v0] = true;
                P[i][i] = true;
            }
        }

        D[v0] = 0;
        final[v0] = true;

        for (int k = 0; k < vexnum; ++k)
        {
            int min = INFINITY;
            int v = k;
            for (int w = 0; w < vexnum; ++w)
            {
                if (!final[w])
                    if (D[w] < min)
                    {
                        v = w;
                        min = D[w];
                    }
            }
            final[v] = true;
            for (int w = 0; w < vexnum; ++w)
            {
                if (!final[w] && (min + matrix[v][w].adj < D[w]))
                {
                    D[w] = min + matrix[v][w].adj;
//                    P[w] = P[v];
                    P[w][w] = true;
                }
            }
        }
    }


private:

    static const int MAX_VERTEX_NUM = 20;
    static const int INFINITY = 100;

    ArcCell matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM] = {0};
    int vexs[MAX_VERTEX_NUM] = {0};
    int vexnum = 0,arcnum = 0; //定点数和弧数
    GraphKind kind;

};

#endif //DATASTRUCTURE_ADJMATRIX_H
