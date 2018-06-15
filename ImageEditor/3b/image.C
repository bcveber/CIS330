#include "image.h"
#include <stdlib.h>

//initialize image and pixel data
void image_initialize(Image &img, int width, int height)
{
    //write output image data
    img.width = width;
    img.height = height;
    img.maxval = 255;

    //give memory to output image
    img.data = (Pixel*)malloc(width * height * sizeof(Pixel));
}

//blend pixels with given factor
void blend_pixel(Pixel *p1, Pixel *p2, double factor, Pixel *output)
{
    double factor2 = 1. - factor;
    output->R = (int)(p1->R * factor + p2->R * factor2);
    output->G = (int)(p1->G * factor + p2->G * factor2);
    output->B = (int)(p1->B * factor + p2->B * factor2);
}
