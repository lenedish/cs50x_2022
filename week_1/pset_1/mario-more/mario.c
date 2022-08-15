#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int hight = 0;
    //ask for number of hight
    do
    {
        hight = get_int("Enter hight: ");
    }
    while (hight <= 0 || hight > 8);

    //print first part of piramid
    for (int i = 1; i <= hight; i++)
    {
        for (int j = 0; j < hight; j++)
        {
            if (hight - j > i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");

        //print second part of piramid
        for (int k = 0; k < hight; k++)
        {
            if (k < i)
            {
                printf("#");
            }
        }
        printf("\n");
    }
}