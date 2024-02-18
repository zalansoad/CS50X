#include "helpers.h"
#include <math.h>

// round() integers

// Convert image to grayscale
// image[2][3].rgbtRed = 0
// dupla for loop
// divide the sum of these integers by 3.0
//.filter -g infile.bmp outfile.bmp
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int atlag = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            atlag = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = atlag;
            image[i][j].rgbtGreen = atlag;
            image[i][j].rgbtRed = atlag;
        }
    }
    return;
}

// Convert image to sepia
// round it
// cap 250
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int blue;
    int green;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);

            red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            if (blue > 255)
            {
                blue = 255;
            }

            if (green > 255)
            {
                green = 255;
            }

            if (red > 255)
            {
                red = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

// Reflect image horizontally
// In the reflect function, you’ll need to swap the values of pixels on opposite sides of a row.
// Recall from lecture how we implemented swapping two values with a temporary variable. No need to use a separate function for
// swapping unless you would like to!
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // bal felso sarok-----ok
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
            }
            // bal also sarok------ok
            else if (i == (height - 1) && j == 0)
            {
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
            }
            // jobb also sarok----------ok
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 4.0);
            }
            // jobb felso sarok-----------ok
            else if (i == (height - 1) && j == (width - 1))
            {
                image[i][j].rgbtRed = round(
                    (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 4.0);
                image[i][j].rgbtGreen = round(
                    (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) /
                    4.0);
                image[i][j].rgbtBlue = round(
                    (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 4.0);
            }

            else if (i == 0) // FELSŐ SOR OK---------------
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                             6.0);
            }

            else if (i == height - 1) // ALSÓ SOR OK --------------
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                                             6.0);
            }

            else if (j == 0) // BAL OSZLOP ok --------------
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                              copy[i][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue) /
                                             6.0);
            }

            else if (j == width - 1) // jobb oszlop ok ----------
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) /
                                            6.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) /
                          6.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i - 1][j].rgbtBlue +
                                              copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) /
                                             6.0);
            }

            else
            {
                image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                                             copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                                            9.0);
                image[i][j].rgbtGreen =
                    round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          9.0);
                image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue +
                                              copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                                              copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                                             9.0);
            }
        }
    }

    return;
}
