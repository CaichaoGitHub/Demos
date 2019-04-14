//
// Created by caichao on 2019-03-23.
//

#ifndef DATASTRUCTURE_SPARSEMATRIX_H
#define DATASTRUCTURE_SPARSEMATRIX_H

#define kMaxSize 1500
#import <iostream>
#include<iomanip>
#include <typeinfo>

class SparseMatrix
{

public:

    static void Test()
    {
//        SparseMatrix sm;
//        sm.Log();
////        sm.Transpose();
////        sm.Log();
//        sm.FastTranspose();
//        sm.Log();

        float mat1[2][3] = {
            {0,1,2},
            {0,2,0},
        };
        float mat2[3][5] = {
            {3,2,0,0,2},
            {0,2,0,1,0},
            {1,0,2,2,0}
        };

        int a[0];
        int *aptr = a;

//        float (*pptr)[3] = mat1;
//        float **ptr = mat1;

//        auto type = typeid(mat1).name();


        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                float v = *(((float*)mat1 + i * 3) + j);
                if (v)
                {

                }
            }
        }

        SparseMatrix sparseMatrix((float**)mat1,2,3);
        sparseMatrix.Log();
        SparseMatrix sparseMatrix1((float**)mat2,3,5);
        sparseMatrix1.Log();

        SparseMatrix res = sparseMatrix * sparseMatrix1;
        res.Log();

    }

    SparseMatrix(){

        mu = 10;
        nu = 10;


        int index = 0;
        for (int i = 0; i < 10; ++i) //row base data
        {
            rpot[i] = index;
            for (int j = 0; j < 4; ++j)
            {
                data[index].row = i;
                data[index].col = j + 1;
                data[index].e = arc4random() % 100;

                index ++;
            }
        }

        tu  = index;

//        Log();

    }

    SparseMatrix(float** array, int row , int col)
    {
        mu = row;
        nu = col;
        for (int i = 0; i < row; ++i)
        {
            rpot[i] = tu;
            for (int j = 0; j < col; ++j)
            {

                float v = *(((float*)array + col * i) + j);
                if (v)
                {
                    data[tu].row = i;
                    data[tu].col = j;
                    data[tu].e = v;
                    ++tu;
                }
            }
        }
    }

    SparseMatrix&operator*(const SparseMatrix &sparseMatrix)
    {
        //fast
        Triple newData[kMaxSize];
        int newMu = mu;
        int newNu = sparseMatrix.nu;
        int newTu = 0;
        float coltmp[kMaxSize] = {0}; //计算每一行的和

        for (int i = 0; i < mu; ++i) //针对每一行
        {
            memset(coltmp,0,kMaxSize);
            int row1begin = rpot[i];
            int row1End = i < mu - 1 ? rpot[i + 1] : tu;

            for (int j = row1begin; j < row1End ; ++j) //对第每行，每列的非0值
            {
                int row2 = data[j].col;
                int row2Begin = sparseMatrix.rpot[row2];
                int row2End = row2 < sparseMatrix.mu - 1 ? sparseMatrix.rpot[row2 + 1] : sparseMatrix.tu;
                for (int k = row2Begin; k < row2End; ++k) //对指定行的非0值，这个行同前面矩阵的列值
                {
                    coltmp[sparseMatrix.data[k].col] += data[j].e * sparseMatrix.data[k].e; //求和
                }
            }

            for (int l = 0; l < newNu; ++l)
            {
                if (coltmp[l] != 0) //压缩
                {

                    newData[newTu].row = i;
                    newData[newTu].col = l;
                    newData[newTu].e = coltmp[l];
                    newTu ++;

                }
            }
        }

        for (int m = 0; m < newTu; ++m)
        {
            data[m] = newData[m];
        }
        mu = newMu;
        nu = newNu;
        tu = newTu;

        return *this;
    }

    void Transpose(){

        //col base transpose
        Triple newData[kMaxSize];
        int index = 0;
        for (int i = 0; i < nu; ++i)
        {
            for (int j = 0; j < tu; ++j)
            {
                if (data[j].col == i)
                {
                    newData[index].col  = data[j].row;
                    newData[index].row = data[j].col;
                    newData[index].e = data[j].e;
                    index ++;
                }
            }
        }

        for (int k = 0; k < tu; ++k)
        {
            data[k].col = newData[k].col;
            data[k].row = newData[k].row;
            data[k].e = newData[k].e;
        }

    }

    void FastTranspose(){

        int num[kMaxSize] = {0};
        int cpot[kMaxSize] = {0};
        for (int i = 0; i < tu; ++i) //get count of col
        {
            ++ num[data[i].col];
        }

        for (int j = 1; j < tu; ++j)
        {
            cpot[j] = cpot[j-1] + num[j - 1];
            this->cpot[j] = cpot[j];
        }

        Triple newData[kMaxSize];
        for (int k = 0; k < tu; ++k)
        {
            int index = cpot[data[k].col];
            newData[index].col  = data[k].row;
            newData[index].row = data[k].col;
            newData[index].e = data[k].e;
            ++cpot[data[k].col];
        }

        for (int k = 0; k < tu; ++k)
        {
            data[k].col = newData[k].col;
            data[k].row = newData[k].row;
            data[k].e = newData[k].e;
        }
    }

    void Log()
    {
        std::cout << std::endl;
//        std::cout.precision(2);
        for (int i = 0; i < mu; ++i)
        {
            for (int j = 0; j < nu; ++j)
            {
                bool find = false;
                for (int k = 0; k < mu * nu; ++k)
                {
                    if (data[k].row == i && data[k].col  == j)
                    {
                        find = true;
                        std::cout.setf(std::ios::right);
                        std::cout << std::setw(2)<< std::setfill('0') << data[k].e << " ";
                        break;
                    }
                }
                if (!find)
                {
                    std::cout <<std::setw(2)<< std::setfill('0') << 0 << " ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        for (int l = 0; l < tu; ++l)
        {
            Triple &t = data[l];
            std::cout  << t.row << " " << t.col << " " << t.e << " " << std::endl;
        }
        std::cout << std::endl;
    }

private:
    struct Triple{
        int row,col;
        float e;
    };

    int cpot[kMaxSize] = {0};
    int rpot[kMaxSize] = {0};
    Triple data[kMaxSize];
    int mu = 0,nu = 0,tu = 0; //row, col, non-zero
};

#endif //DATASTRUCTURE_SPARSEMATRIX_H
