#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    char *file = argv[1];
    FILE *input = fopen(file, "r");

    if (input == NULL)
    {
        printf("Error 2");
        return 2;
    }

    BYTE buffer[BLOCK_SIZE];
    int counter = 0;
    char filename[12];
    FILE *img = NULL;

    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, input))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", counter++);
            img = fopen(filename, "w");
        }

        if (img != NULL)
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }


    fclose(input);
}