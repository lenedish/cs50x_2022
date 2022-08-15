#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int numbers[] = {2, 1, 1, 0};
    int min = numbers[0];

    for (int j = 0; j < 4; j++)
    {
        if (min > numbers[j])
        {
            min = numbers[j];
        }
    }
    printf("Min: %i\n", min);
}