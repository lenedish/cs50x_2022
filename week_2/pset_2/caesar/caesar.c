#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_key(string key);
string encript_text(string text, int key);

int main(int argc, string argv[])
{
    int key = 0;
    if (argc == 2)
    {
        if (check_key(argv[1]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
        else
        {
            key = check_key(argv[1]);
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    string ciphertext = encript_text(plaintext, key);

    printf("%s\n", ciphertext);

    return 0;
}

int check_key(string key)
{
    for (int i = 0, lenght = strlen(key); i < lenght; i++)
    {
        if (isdigit(key[i]) == 0)
        {
            return 0;
        }
    }
    return atoi(key);
}

string encript_text(string text, int key)
{
    printf("ciphertext: ");
    for (int i = 0, lenght = strlen(text); i < lenght; i++)
    {
        if (isalpha(text[i]))
        {
            if (islower(text[i]))
            {
                text[i] = text[i] - 97;
                text[i] = (text[i] + key) % 26;
                text[i] = text[i] + 97;
            }
            else
            {
                text[i] = text[i] - 65;
                text[i] = (text[i] + key) % 26;
                text[i] = text[i] + 65;
            }
        }
    }
    return text;
}