#include <stdio.h>

int main(void)
{
    char *string = "HI!";
    char *pointer = &string[0];
    printf("%s\n", string);
    printf("%p\n", pointer);
    printf("%c\n", *string);
    printf("%c\n", *(string + 1));
    printf("%c\n", *(string + 2));

}