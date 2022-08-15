#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_key(string key);
void encript_text(string text, string key);

// Шифрует текст на основе полученного ключа
int main(int argc, string argv[])
{
    int key = 0;
    if (argc == 2)
    {
        if (check_key(argv[1]) == 0)
        {
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    encript_text(plaintext, argv[1]);

    return 0;
}
// Проверяет валидность ключа
int check_key(string key)
{
    int lenght = strlen(key);
    if (lenght == 26)
    {
        for (int i = 0; i < lenght; i++)
        {
            if (isalpha(key[i]) == 0)
            {
                printf("Key must only contain alphabetic characters.\n");
                return 0;
            }
            // Переводит любые буквы в lowercase
            else if (isupper(key[i]))
            {
                key[i] = tolower(key[i]);
            }
            // Находит повторяющие символы в ключе
             for (int j = 0; j < lenght; j++)
             {
                 int count = 0;
                 for (int k = 0; k < lenght; k++)
                 {
                     if (key[j] == key[k])
                     {
                         count++;
                     }
                 }
                 if (count > 1)
                 {
                     printf("Count: %i\n", count);
                     printf("Key must not contain repeated characters.\n");
                     return 0;
                 }
             }
        }
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 0;
    }
    return 1;
}

//Шифрует текст
void encript_text(string text, string key)
{
    int lenght = strlen(text);
    char ciphertext[lenght];

    for (int i = 0; i < lenght; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                ciphertext[i] = toupper(key[text[i] - 65]);
            }
            else
            {
                ciphertext[i] = key[text[i] - 97];
            }
        }
        else
        {
            ciphertext[i] = text[i];
        }
    }
    // Печатает текст
    printf("ciphertext: ");
    for (int i = 0; i < lenght; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}