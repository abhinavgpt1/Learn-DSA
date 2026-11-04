#include <stdio.h>
int main()
{
    if (1)
        if (0) // this if is associated with above if
            printf("if-if\n");
        else // [IMP] this else is associated with above if, not with first if
            printf("if-if-else\n");
    else if (1)
        printf("if-elseif\n");
    else
        printf("if-else\n");
    printf("outside, since one statement is allowed without braces\n");
}

/**
 * Output:
 * -------
 * if-if-else
 * outside, since one statement is allowed without braces
 */