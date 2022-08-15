#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *x = malloc(12);

    printf("x: ");
    scanf("%s", x);
    printf("x: %s\n", x);
}