#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *x;
    int *y;

    x = malloc(sizeof(int));

    *x = 34;
    y = x;
    *y = 64;

    printf("%i\n", *x);
}