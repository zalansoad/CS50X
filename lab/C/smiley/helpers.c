#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing


    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            if(image[i][j].rgbtBlue == 000 && image[i][j].rgbtGreen == 000 && image[i][j].rgbtRed == 000)
            {
                image[i][j].rgbtBlue = 143;
                image[i][j].rgbtGreen = 000;
                image[i][j].rgbtRed = 255;
            }
        }
    }
}
