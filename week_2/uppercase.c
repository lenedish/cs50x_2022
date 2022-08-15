#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (void) {
    string name = get_string("Enter name: ");
    int lenght = strlen(name);

    for (int i = 0; i < lenght; i++) {
        if(islower(name[i]) !=  0) {
            printf("%c", name[i] - 32);
        }
        else {
            printf("%c", name[i]);
        }

    }
    printf("\n");
}
