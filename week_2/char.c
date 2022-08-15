#include <stdio.h>
#include <cs50.h>

int get_lenght(string s);

int main (void) {
    string s = get_string("Enter string: ");

    int lenght = get_lenght(s);
    printf("%i\n", lenght);
}

int get_lenght(string s) {
    int i = 0;
    while (s[i] != '\0')
    {
        i++;
    }
    return i;
}