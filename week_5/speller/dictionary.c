// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include "dictionary.h"
#include <string.h>
#include <stdlib.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 3060;

// Hash table
node *table[N];

// Pointer of variable size

int sizeVariable = 0;
int *sizeTmp = &sizeVariable;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];
    if (cursor == NULL)
    {
        return false;
    }

    while (cursor != NULL)
    {
        node *next = (*cursor).next;
        if (strcasecmp(word, (*cursor).word) == 0)
        {
            return true;
        }
        else
        {
            cursor = next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int lenght = strlen(word);
    int hashValue = 0;

    for (int i = 0; i < lenght; i++)
    {
        hashValue = hashValue + toupper(word[i]);
    }

    return hashValue;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];

    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return 1;
        }

        strcpy((*n).word, word);

        (*n).next = NULL;

        if (table[hash(word)] != NULL)
        {
            (*n).next = table[hash(word)];
        }

        table[hash(word)] = n;

        *sizeTmp = *sizeTmp + 1;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // if (*sizeTmp == 0)
    // {
    //     return 0;
    // }

    return *sizeTmp;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp;
        node *next;

        if (cursor != NULL)
        {
            while (cursor != NULL)
            {
                tmp = cursor;
                next = (*cursor).next;

                free(tmp);

                cursor = next;
            }
        }
    }

    return true;
}
