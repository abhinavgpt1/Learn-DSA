#include<stdio.h>
int main()
{
    if(1)
        if(0)
            printf("if if\n");
        else
            printf("if mein else\n");
    else
        if(1)
            printf("it is actual else if statement\n");
        else
            printf("else 2\n");
    printf("outside\n");

}