#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            float average = (blue + green + red) / 3;

            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);
            image[i][j].rgbtRed = round(average);
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
            float blue = image[i][j].rgbtBlue;
            float green = image[i][j].rgbtGreen;
            float red = image[i][j].rgbtRed;

            double sepia_red = round((red * 0.393 + green * 0.769 + blue * 0.189));
            double sepia_green = round((red * 0.349 + green * 0.686 + blue * 0.168));
            double sepia_blue = round((red * 0.272 + green * 0.534 + blue * 0.131));

            //this does look ugly
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }
            if (sepia_blue < 0)
            {
                sepia_blue = 0;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            if (sepia_green < 0)
            {
                sepia_green = 0;
            }
            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            if (sepia_red < 0)
            {
                sepia_red = 0;
            }

            image[i][j].rgbtBlue = sepia_blue;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtRed = sepia_red;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //find half way point
    int half_way = round((float)width / 2.0);
    //loop until half way point, while counting downwards(i) and upwards(n), replacing one with the other
    for (int row = 0; row < height; row++)
    {
        int n = 0;
        for (int i = width; i > half_way; i--)
        {
            RGBTRIPLE temp = image[row][n];
            image[row][n] = image[row][i - 1];
            image[row][i - 1] = temp;
            n++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //i need a temporary array to store values, if not they result of the next pixel will be based of the before blured pixel
    RGBTRIPLE temp[height][width];
    //loop rows
    for (int i = 0; i < height; i++)
    {
        //loop columns
        for (int j = 0; j < width; j++)
        {
            //initialize
            int sum_blue = 0;
            int sum_green = 0;
            int sum_red = 0;
            int pixels_found = 0;

            //loop each pixel next to bluring pixel, if doesnt exitst then skip
            for (int h = -1; h < 2; h++)
            {
                for (int w = -1; w < 2; w++)
                {
                    if (i + h < 0 || i + h > (height - 1))
                    {
                        continue;
                    }
                    if (j + w < 0 || j + w > (width - 1))
                    {
                        continue;
                    }
                    sum_blue += image[i + h][j + w].rgbtBlue;
                    sum_green += image[i + h][j + w].rgbtGreen;
                    sum_red += image[i + h][j + w].rgbtRed;
                    pixels_found++;
                }
            }
            temp[i][j].rgbtBlue = round((float)sum_blue / (float)pixels_found);
            temp[i][j].rgbtGreen = round((float)sum_green / (float)pixels_found);
            temp[i][j].rgbtRed = round((float)sum_red / (float)pixels_found);
        }
    }
    //assign temp array back to normal array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
