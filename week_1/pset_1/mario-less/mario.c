#include <stdio.h>
#include <cs50.h>

//ask for number of hight and then print piramid
int main(void)
{
    int hight = 0;
    //ask for number of hight
    do
    {
        hight = get_int("Enter hight: ");
    }
    while (hight <= 0 || hight > 8);

    //print piramid
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
        printf("\n");
    }
}
