#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    node *list = NULL;

    // Create node 1
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    (*n).number = 1;
    (*n).next = NULL;

    list = n;

    // Create node 2
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }

    (*n).number = 2;
    (*n).next = NULL;

    (*list).next = n;

    // Print list
    for (node *tmp = list; tmp != NULL; tmp = (*tmp).next)
    {
        printf("%i\n", (*tmp).number);
    }

    // Free list
    while (list != NULL)
    {
        node *tmp = (*list).next;
        free(list);
        list = tmp;
    }
}