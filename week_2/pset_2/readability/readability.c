#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int calculate_index(string text);

int main(void)
{
    int index = 0;

    string text = get_string("Text: ");
    index = calculate_index(text);

    if (index < 1) {
        printf("Before Grade 1\n");
    }
    else if (index > 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", index);
    }

}

int calculate_index(string text) {
    float index = 0;
    float letters = 0;
    float words = 1;
    float sentenses = 0;
    float l = 0;
    float s = 0;
    int result = 0;

    for (int i = 0, lenght = strlen(text); i < lenght; i++) {
        if (isupper(text[i])) {
            text[i] = tolower(text[i]);
        }

        if (text[i] == 32) {
            words++;
        }
        else if (text[i] == 46 || text[i] == 63 || text[i] == 33) {
            sentenses++;
        }
        else if (text[i] >= 97 && text[i] <= 122) {
            letters++;
        }
    }

    l = (letters / words) * 100.0;
    s = (sentenses / words) * 100.0;

    index = 0.0588 * l - 0.296 * s - 15.8;

    return round(index);
}