#ifndef IMAGE_H
#define IMAGE_H

//pixel structure
typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
} Pixel;

class Image
{
    Pixel* buffer;
    int width, height, maxval;
public:
    int getWidth();
    int getHeight();
    int getMaxVal();
    Pixel* getBuffer();             //get pointer to image buffer
    void initialize(int w, int h);   //set new image buffer
};

#endif
