//
// Created by caichao on 2019-03-21.
//

#ifndef DATASTRUCTURE_ARRAYSTACK_H
#define DATASTRUCTURE_ARRAYSTACK_H

#include <iostream>


#define kInitSize 100


template <typename T>

class ArrayStack
{
public:

    static void Test()
    {
        ArrayStack<int> st;
        st.Push(1);
        st.Push(2);
        st.Push(3);
        st.Traverse();
        st.Pop();
        st.Traverse();
        st.Pop();
        st.Pop();
        st.Pop();

        //十进制转 八进制
        printf("input a value to convert \n");
        int N;
        scanf("%d",&N);
        while (N)
        {
            st.Push(N%8);
            N = N / 8;
        }

        while (!st.Empty())
        {
            std::cout  << st.Pop() << " ";
        }
        std::cout << std::endl;

        //
        printf("括号匹配 输入[](){} \n");

        char cc;
        fflush(stdin);
        scanf("%c",&cc);
        ArrayStack<char> sttt;
        sttt.Push(cc);
        while (!sttt.Empty())
        {
            printf("括号匹配 输入[](){} \n");
            scanf("%c",&cc);
            fflush(stdin);
            if (sttt.Top() == cc)
            {
                sttt.Pop();
            }
            else
            {
                sttt.Push(cc);
            }
            sttt.Traverse();
        }

        std::cout << "all stack has finished" << std::endl;
    }

    static void Test2()
    {
        ArrayStack<char> stack;

        char ch = getchar();
        while (ch != EOF)
        {
            while (ch != '\n')
            {
                switch (ch)
                {
                    case '@':
                    {
                        stack.Clear();
                    }
                        break;
                    case '#':
                    {
                        stack.Pop();
                    }
                        break;
                    default:
                    {
                        stack.Push(ch);
                    }
                        break;
                }
                ch = getchar();
            }
            stack.Traverse();
            stack.Clear();
            ch = getchar();
        }
    }

    ArrayStack(){
        stack_.base = new T[kInitSize];
        stack_.top = stack_.base;
        stack_.stackSize = kInitSize;
    }

    T &Top()
    {
        return *stack_.top;
    }

    void Push(T e)
    {
        stack_.top ++;
        *stack_.top = e;
    }

    T Pop()
    {
        if (stack_.top != stack_.base)
        {
            T e = *stack_.top;
            stack_.top --;
            return e;
        }
        return 0;
    }

    void Clear()
    {
        stack_.top = stack_.base;
    }

    bool Empty(){return stack_.top == stack_.base;}

    void Traverse(){
        std::cout << std::endl;
        T *top = stack_.top;
        while (top != stack_.base)
        {
            std::cout << "v:" << *top << " " ;
            --top;
        }
        std::cout << std::endl;
    }

private:

    struct SqStack{
        T *base;
        T *top;
        int stackSize;
    };

    SqStack stack_;

};

#endif //DATASTRUCTURE_ARRAYSTACK_H
