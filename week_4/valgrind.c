#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *numbers = malloc(sizeof(int) * 3);

    numbers[0] = 72;
    numbers[1] = 73;
    numbers[2] = 33;

    free(numbers);
}