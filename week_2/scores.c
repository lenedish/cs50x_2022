#include <stdio.h>
#include <cs50.h>

int main (void) {

    int num = get_int("Enter number of scores");
    int scores[num];
    int sum = 0;

    for (int i = 0; i < num; i++) {
        scores[i] = get_int("Ecter score: ");
    }

    for (int j = 0; j < num; j++) {
        sum = sum + scores[j];
    }

    printf("%f\n", sum / 3.0);
}