#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            float result = (red + green + blue) / 3.0;

            int average = round(result);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int sepiaRed = round((red * .393) + (green * .769) + (blue * .189));
            int sepiaGreen = round((red * .349) + (green * .686) + (blue * .168));
            int sepiaBlue = round((red * .272) + (green * .534) + (blue * .131));

            if (sepiaRed > 255 || sepiaRed < 0)
            {
                if (sepiaRed > 255)
                {
                    sepiaRed = 255;
                }
                else
                {
                     sepiaRed = 0;
                }
            }

            if (sepiaGreen > 255 || sepiaGreen < 0)
            {
                if (sepiaGreen > 255)
                {
                    sepiaGreen = 255;
                }
                else
                {
                     sepiaGreen = 0;
                }
            }

            if (sepiaBlue > 255 || sepiaBlue < 0)
            {
                if (sepiaBlue > 255)
                {
                    sepiaBlue = 255;
                }
                else
                {
                     sepiaBlue = 0;
                }
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int half = width / 2;

    int tempRed[width / 2];
    int tempGreen[width / 2];
    int tempBlue[width / 2];

    for (int i = 0; i < height; i++)
    {
        // Half one
        for (int j = 0; j < half; j++)
        {
            tempRed[j] = image[i][j].rgbtRed;
            tempGreen[j] = image[i][j].rgbtGreen;
            tempBlue[j] = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

        }
         // Half two
        for (int k = 0; k < half; k++)
        {
            image[i][width - k - 1].rgbtRed = tempRed[k];
            image[i][width - k - 1].rgbtGreen = tempGreen[k];
            image[i][width - k - 1].rgbtBlue = tempBlue[k];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        BYTE  rgbtBlue;
        BYTE  rgbtGreen;
        BYTE  rgbtRed;
    }
    RGBTRIPLE_BLURE;

    RGBTRIPLE_BLURE imageBlur[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageBlur[i][j].rgbtRed = image[i][j].rgbtRed;
            imageBlur[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageBlur[i][j].rgbtBlue = image[i][j].rgbtBlue;

            int red = 0;
            int green = 0;
            int blue = 0;

            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;

            int redAverage = 0;
            int greenAverage = 0;
            int blueAverage = 0;

            if ((i == 0 && j == 0) || (i == 0 && j == (width - 1)) || (i == (height - 1) && j == 0) || (i == (height - 1) && j == (width - 1)))
            {
                if (i == 0 && j == 0)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int h = 0; h < 2; h++)
                        {
                            red = image[i  + k][j + h].rgbtRed;
                            green = image[i  + k][j + h].rgbtGreen;
                            blue= image[i + k][j + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 4.0);
                    greenAverage = round(greenSum / 4.0);
                    blueAverage = round(blueSum / 4.0);
                }
                else if (i == 0 && j == (width - 1))
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int h = 0; h < 2; h++)
                        {
                            red = image[i + k][(j - 1) + h].rgbtRed;
                            green = image[i + k][(j - 1) + h].rgbtGreen;
                            blue= image[i + k][(j - 1) + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 4.0);
                    greenAverage = round(greenSum / 4.0);
                    blueAverage = round(blueSum / 4.0);
                }
                else if (i == (height - 1) && j == 0)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int h = 0; h < 2; h++)
                        {
                            red = image[(i - 1) + k][j + h].rgbtRed;
                            green = image[(i - 1) + k][j + h].rgbtGreen;
                            blue= image[(i - 1) + k][j + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 4.0);
                    greenAverage = round(greenSum / 4.0);
                    blueAverage = round(blueSum / 4.0);
                }
                else if (i == (height - 1) && j == (width - 1))
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int h = 0; h < 2; h++)
                        {
                            red = image[(i - 1) + k][(j - 1) + h].rgbtRed;
                            green = image[(i - 1) + k][(j - 1) + h].rgbtGreen;
                            blue= image[(i - 1) + k][(j - 1) + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 4.0);
                    greenAverage = round(greenSum / 4.0);
                    blueAverage = round(blueSum / 4.0);
                }
            }
            else if (i == 0 || j == 0 || i == (height - 1) || j == (width - 1))
            {
                if (i == 0)
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int h = 0; h < 3; h++)
                        {
                            red = image[i + k][(j - 1) + h].rgbtRed;
                            green = image[i + k][(j - 1) + h].rgbtGreen;
                            blue= image[i + k][(j - 1) + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 6.0);
                    greenAverage = round(greenSum / 6.0);
                    blueAverage = round(blueSum / 6.0);
                }
                else if (j == 0)
                {
                    for (int k = 0; k < 3; k++)
                    {
                        for (int h = 0; h < 2; h++)
                        {
                            red = image[(i - 1) + k][j + h].rgbtRed;
                            green = image[(i - 1) + k][j + h].rgbtGreen;
                            blue= image[(i - 1) + k][j + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 6.0);
                    greenAverage = round(greenSum / 6.0);
                    blueAverage = round(blueSum / 6.0);
                }
                else if (j == (width - 1))
                {
                    for (int k = 0; k < 3; k++)
                    {
                        for (int h = 0; h < 2; h++)
                        {
                            red = image[(i - 1) + k][(j - 1) + h].rgbtRed;
                            green = image[(i - 1) + k][(j - 1) + h].rgbtGreen;
                            blue= image[(i - 1) + k][(j - 1) + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 6.0);
                    greenAverage = round(greenSum / 6.0);
                    blueAverage = round(blueSum / 6.0);
                }
                else if (i == (height - 1))
                {
                    for (int k = 0; k < 2; k++)
                    {
                        for (int h = 0; h < 3; h++)
                        {
                            red = image[(i - 1) + k][(j - 1) + h].rgbtRed;
                            green = image[(i - 1) + k][(j - 1) + h].rgbtGreen;
                            blue= image[(i - 1) + k][(j - 1) + h].rgbtBlue;

                            redSum += red;
                            greenSum += green;
                            blueSum += blue;
                        }
                    }
                    redAverage = round(redSum / 6.0);
                    greenAverage = round(greenSum / 6.0);
                    blueAverage = round(blueSum / 6.0);
                }
            }
            else
            {
                for (int k = 0; k < 3; k++)
                {
                    for (int h = 0; h < 3; h++)
                    {
                        red = image[(i - 1) + k][(j - 1) + h].rgbtRed;
                        green = image[(i - 1) + k][(j - 1) + h].rgbtGreen;
                        blue= image[(i - 1) + k][(j - 1) + h].rgbtBlue;

                        redSum += red;
                        greenSum += green;
                        blueSum += blue;
                    }
                }
                redAverage = round(redSum / 9.0);
                greenAverage = round(greenSum / 9.0);
                blueAverage = round(blueSum / 9.0);
            }

            imageBlur[i][j].rgbtRed = redAverage;
            imageBlur[i][j].rgbtGreen = greenAverage;
            imageBlur[i][j].rgbtBlue = blueAverage;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imageBlur[i][j].rgbtRed;
            image[i][j].rgbtGreen = imageBlur[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imageBlur[i][j].rgbtBlue;
        }
    }
    return;
}
