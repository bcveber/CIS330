#include "functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//reads the PNM/P6 file, returns an image struct
void ReadImage(char *filename, Image &output)
{
    FILE *f_in;
    int width, height, maxval;
    char magicNum[128];

    //read file with read binary mode
    f_in = fopen(filename, "rb");

    //check if file was opened successfully
    if (!f_in)
    {
	//if it wasn't then exit
        return;
    }

    //read header of image file
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

    //only work with P6 format currently
    if (strcmp(magicNum, "P6"))
    {
	//if it isn't P6 then exit
        return;
    }

    //initialize image
    image_initialize(output, width, height);

    //read pixels
    //height * width = num of structs to read
    fread(output.data, sizeof(Pixel), (output.height * output.width), f_in);

    //close file
    fclose(f_in);
}

//write image
void WriteImage(char *filename, Image &img)
{
    FILE *f_in;

    //read file with read binary mode
    f_in = fopen(filename, "wb");

    //write image header
    fprintf(f_in, "%s\n%d %d\n%d\n", "P6", img.width, img.height, img.maxval);

    //write the elements
    fwrite(img.data, sizeof(Pixel), (img.width * img.height), f_in);

    //close file
    fclose(f_in);
}

//reduce image size to half
void HalfSize(Image &input, Image &output)
{
    int x, y, n1, n2;
    int width = input.width / 2;
    int height = input.height / 2;

    //initialize image
    image_initialize(output, width, height);

    //copy data
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //output[y][x] = input[y*2][x*2]
            n1 = (y*width) + x;
            n2 = (y*2*input.width) + (x*2);

            //copy pixel info
            output.data[n1] = input.data[n2];
        }
    }
}

void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output)
{
    int x, y, n1, n2;
    int width = leftInput.width + rightinput.width;
    int height = leftInput.height;

    //initialize image
    image_initialize(output, width, height);

    //combine images (left+right)
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //pixel in output image
            n1 = (y*width) + x;

            //check what pixel we have
            //copy pixel info
            if (x >= leftInput.width)
            {
                n2 = (y * rightinput.width) + x - leftInput.width;
                output.data[n1] = rightinput.data[n2];
            }
            else
            {
                n2 = (y * leftInput.width) + x;
                output.data[n1] = leftInput.data[n2];
            }
        }
    }
}

void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output)
{
    int x, y, n1, n2;
    int width = topInput.width;
    int height = topInput.height + bottomInput.height;

    //initialize image
    image_initialize(output, width, height);

    //combine images (top+bottom)
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //pixel in output image
            n1 = (y * width) + x;

            //check what pixel we have
            //copy pixel info
            if (y >= topInput.height)
            {
                n2 = ((y - topInput.height) * bottomInput.width) + x;
                output.data[n1] = bottomInput.data[n2];
            }
            else
            {
                n2 = (y * topInput.width) + x;
                output.data[n1] = topInput.data[n2];
            }
        }
    }
}

void Blend(Image &input1, Image &input2, double factor, Image &output)
{
    int x, y, n;
    int width = input1.width;
    int height = input1.height;

    //initialize image
    image_initialize(output, width, height);

    //blend images
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //pixel in output image
            n = (y * width) + x;

            //blend
            blend_pixel(input1.data + n, input2.data + n, factor, output.data + n);
        }
    }
}
