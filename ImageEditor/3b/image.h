#ifndef IMAGE_H
#define IMAGE_H

//pixel structure
typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
} Pixel;

typedef struct
{
    //width of image
    int width;

    //height of image
    int height;

    //max value of pixel
    int maxval;

    //pointer to array of pixel info
    Pixel* data;
} Image;

//initialize image and blend pixels
void image_initialize(Image &img, int width, int height);
void blend_pixel(Pixel *p1, Pixel *p2, double factor, Pixel *output);

#endif
