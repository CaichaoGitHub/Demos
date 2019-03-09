#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isHead(int index)
{
    if (index % 2 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    char input[] = "123##67#######8";
    char s = '\n';
    int c_index = 0;
    char ps = '\n';
    
    do
    {
        s = input[c_index];
        
        if (isHead(c_index))
        {
            printf("%c \t",s);
        }
        else if (s == '#')
        {
            continue;
        }
        else
        {
            if(ps == '#')
            {
                printf("%c \t",s);
            }
        }
        
        c_index ++;
        ps = s;
        
    }while(s != '\n');
    
    /*for (int i = 0,i < c_length; i++)
     {
     
     }*/
    
    
    
    
    
    
    
    
    
    
    return 0;
}
