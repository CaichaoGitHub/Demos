//
// Created by caichao on 2019-03-23.
//

#ifndef DATASTRUCTURE_STRING_H
#define DATASTRUCTURE_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class String
{
public:

    static void Test()
    {
        String s("abc");
        s.Log();
        String ss("ababc");
        ss.Log();
        int i = ss.IndexOf(s);
        int j = ss.QuickIndexOf(s);
        printf("d");
    }

    String(char *string)
    {
        int charlen = CharLength(string);
        if (charlen > 0)
        {
            if (charlen >= storge.size)
            {
                storge.ch = (char*)realloc(storge.ch,(charlen + 1)* sizeof(char));

                storge.size = charlen;
                storge.length = charlen;
                for (int i = 0; i < charlen; ++i)
                {
                    storge.ch[i] = string[i];
                }
                storge.ch[charlen] = '\0';
            }
            else
            {
                storge.length = charlen;
                for (int i = 0; i < charlen; ++i)
                {
                    storge.ch[i] = string[i];
                }
                storge.ch[charlen] = '\0';
            }
            storge.next = new int[charlen];
            for (int j = 0; j < charlen; ++j)
            {
                storge.next[j] = 0;
            }
        }
        PrepareNext();
    }


    int IndexOf(String &s)
    {
        if (s.storge.length < storge.length)
        {
            int i = 0, j = 0;
            int startIndex = 0;
            while (i < s.storge.length && j < storge.length)
            {
                if (s.storge.ch[i] == storge.ch[j])
                {
                    i ++ , j ++;
                }
                else
                {
                    i = 0;
                    j = ++startIndex;
                }

            }
            if (i >= s.storge.length)
                return startIndex;
        }
        return 0;
    }

    int QuickIndexOf(String &s)
    {
        //KMP 算法
        if (s.storge.length < storge.length)
        {
            int i = 0;
            int j = 0;
            while (i < s.storge.length && j < storge.length)
            {
                if (i == -1 || s.storge.ch[i] == storge.ch[j])
                {
                    i++,j++;
                }
                else
                {
                    i = s.storge.next[i];
                }
            }
            if (i >= s.storge.length)
                return j - i;
        }
        return 0;
    }

    void PrepareNext()
    {
        int i = 0, k = -1;
        storge.next[0] = -1;
        while (i < storge.length)
        {
            if (k == -1 || storge.ch[i] == storge.ch[k]) //存在长度为K的子串和主串相同
            {
                k ++ ; //next[i] + 1
                i ++;
                storge.next[i] = k;
            }
            else
            {
                k = storge.next[k]; //不存在就就回溯，一直回到最初的位置
            }
        }

        printf("next : ");
        for (int k = 0; k < storge.length; ++k)
        {
            printf("%d ",storge.next[k]);
            fflush(stdout);
        }
        printf("\n");
    }

    void Log()
    {
        printf("%s \n",storge.ch);
        fflush(stdout);
    }



private:

    int CharLength(char *string)
    {
        int ll = strlen(string);
        int len = 0;
        while (string && string[len] != '\0')
        {
            len ++;
        }
        return len;
    }

    struct HString{
        int *next = nullptr;
        int size  = 0;
        char *ch = nullptr;
        int length = 0;
    };
    HString storge;
};

#endif //DATASTRUCTURE_STRING_H
