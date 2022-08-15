#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //prompt from input
    long card = get_long("Enter card number: ");
    long check_strt_num = card;

    //Find out number of digit in a card
    long check_number = card;
    int count = 0;
    while (check_number != 0)
    {
        check_number = check_number / 10;
        count++;
    }

    //calculate checksum
    int last_digit = 0;
    int sum = 0;
    int sum2 = 0;
    int eachnum = 0;
    int last_digit2 = 0;
    int checksum = 0;
    for (int i = 0; i < count; i++)
    {
        if (i % 2 == 0)
        {
            last_digit2 = card % 10;
            sum2 = sum2 + last_digit2;
        }

        if (i % 2 != 0)
        {
            last_digit = card % 10;

            eachnum = last_digit * 2;
            if (eachnum / 10 != 0)
            {
                int temp = 0;
                temp = eachnum % 10;
                sum = sum + (temp + (eachnum / 10));
            }
            if (eachnum / 10 == 0)
            {
                sum = sum + eachnum;
            }
        }

        card = card / 10;
    }
    checksum = sum + sum2;

    //check for card lenght and stating digit
    long first_two = 0;
    long first_one = 0;
    first_one = check_strt_num / 1000000000000000;
    first_two = check_strt_num / 100000000000000;

    if (checksum % 10 != 0)
    {
        printf("INVALID\n");
    }

    else if ((count == 15 && check_strt_num / 10000000000000 == 34) || (count == 15 && check_strt_num / 10000000000000 == 37))
    {
        printf("AMEX\n");
    }
    else if ((count == 16 && first_two == 51) || (count == 16 && first_two == 52) || (count == 16 && first_two == 53) ||
             (count == 16 && first_two == 54) || (count == 16 && first_two == 55))
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 && check_strt_num / 1000000000000 == 4) || (count == 16 && first_one == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}