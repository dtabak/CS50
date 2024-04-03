#include "stdio.h"
#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width ; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width ; j++)
        {
            copy[i][j].rgbtRed = fmin(round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue),255);
            copy[i][j].rgbtGreen = fmin(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue), 255);
            copy[i][j].rgbtBlue = fmin(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue), 255);



           image[i][j].rgbtRed = copy[i][j].rgbtRed;
           image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
           image[i][j].rgbtBlue = copy[i][j].rgbtBlue;

        }

    }
    return;

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j <width/2 ; j++)
            {
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width-1-j];
                image[i][width-1-j] = temp[i][j];
            }
        }
        else if (width % 2 != 0)
        {
            for (int j = 0; j<(width-1)/2 ; j++)
            {
                temp[i][j] = image[i][j];
                image[i][j] = image[i][width-1-j];
                image[i][width-1-j] = temp[i][j];
            }
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
        for (int j = 0; j <width ; j++)
        {

            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <width ; j++)
        {

            // Middle Pixel

            if(i>0 && j>0 && i<height-1 && j<width-1)
            {

            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed) /9.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen) /9.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue) /9.0);
            }

            // Pixel on Edge

            else if(i == 0 && j>0 && j<width-1)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed + copy[i+1][j-1].rgbtRed) /6.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen) /6.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue) /6.0);
            }
            else if(i == height-1 && j>0 && j<width-1)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i-1][j-1].rgbtRed) /6.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i-1][j-1].rgbtGreen) /6.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i-1][j-1].rgbtBlue) /6.0);
            }
            else if(i >0 && i< height-1 && j==0)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i+1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i+1][j+1].rgbtRed) /6.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i+1][j+1].rgbtGreen) /6.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i+1][j+1].rgbtBlue) /6.0);
            }
            else if(i >0 && i< height-1 && j==width-1)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i+1][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i+1][j-1].rgbtRed) /6.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen) /6.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i+1][j-1].rgbtBlue) /6.0);
            }

            // Pixel on Corner

            else if(i==0 && j==0)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j+1].rgbtRed) /4.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i+1][j+1].rgbtGreen) /4.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i+1][j+1].rgbtBlue) /4.0);
            }
            else if(i==height-1 && j==0)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j+1].rgbtRed) /4.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i-1][j+1].rgbtGreen) /4.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i-1][j+1].rgbtBlue) /4.0);
            }
            else if(i==0 && j==width-1)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i+1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i+1][j-1].rgbtRed) /4.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i+1][j-1].rgbtGreen) /4.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i+1][j-1].rgbtBlue) /4.0);
            }
            else if(i==height-1 && j==width-1)
            {
            image[i][j].rgbtRed = round((copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i-1][j-1].rgbtRed) /4.0);
            image[i][j].rgbtGreen = round((copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i-1][j-1].rgbtGreen) /4.0);
            image[i][j].rgbtBlue = round((copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i-1][j-1].rgbtBlue) /4.0);
            }
        }
    }

    return;
}
