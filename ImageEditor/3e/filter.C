#include "filter.h"

#include "image.h"

//filter initializer
Filter::Filter()
{
    img1 = 0;
    img2 = 0;
    img.setSource(this);
}

void Filter::Update()
{
    //update source image1
    if (img1)
        img1->Update();

    //update 2
    if (img2)
        img2->Update();

    //execute current filter
    Execute();
}

//execute shrinker
void Shrinker::Execute()
{
    int x, y, n1, n2;
    Pixel *output, *input;
    int org_width = img1->getWidth();
    int width = img1->getWidth() / 2;
    int height = img1->getHeight() / 2;

    //initialize image
    this->img.initialize(width, height);

    //buffers
    input = img1->getBuffer();
    output = img.getBuffer();

    //copy data
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //output[y][x] = input[y*2][x*2]
            n1 = (y*width) + x;
            n2 = (y*2*org_width) + (x*2);

            //copy pixel info
            output[n1] = input[n2];
        }
    }
}

void LRCombine::Execute()
{
    int x, y, n1, n2;
    Pixel *output, *input_l, *input_r;
    int width = img1->getWidth() + img2->getWidth();
    int height = img1->getHeight();

    //initialize image
    this->img.initialize(width, height);

    //buffers
    input_l = img1->getBuffer();
    input_r = img2->getBuffer();
    output = img.getBuffer();

    //combine images (left+right)
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //pixel in output image
            n1 = (y * width) + x;

            //check what pixel we have and copy pixel info
	    //get pixels row-wise from left image, then start picking from right image
            if (x >= img1->getWidth())
            {
                n2 = (y * img2->getWidth()) + x - img1->getWidth();
                output[n1] = input_r[n2];
            }
            else
            {
                n2 = (y * img1->getWidth()) + x;
                output[n1] = input_l[n2];
            }
        }
    }
}

void TBCombine::Execute()
{
    int x, y, n1, n2;
    Pixel *output, *input_t, *input_b;
    int width = img1->getWidth();
    int height = img1->getHeight() + img2->getHeight();

    //initialize image
    this->img.initialize(width, height);

    //buffers
    input_t = img1->getBuffer();
    input_b = img2->getBuffer();
    output = img.getBuffer();

    //combine images (top+bottom)
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //pixel in output image
            n1 = (y * width) + x;

	    //check what pixel we have and copy pixel info
	    //get pixels column-wise from top image, then start picking from bottom image
            if (y >= img1->getHeight())
            {
                n2 = ((y - img1->getHeight()) * img2->getWidth()) + x;
                output[n1] = input_b[n2];
            }
            else
            {
                n2 = (y * img1->getWidth()) + x;
                output[n1] = input_t[n2];
            }
        }
    }
}

//set blend factor
void Blender::SetFactor(double f)
{
    this->factor = f;
}

//blend pixels with given factor
static void blend_pixel(Pixel *p1, Pixel *p2, double factor, Pixel *output)
{
    //blend_color = (color_1) * factor + (color_2) * factor_2
    double factor2 = 1. - factor;
    output->R = (int)(p1->R * factor + p2->R * factor2);
    output->G = (int)(p1->G * factor + p2->G * factor2);
    output->B = (int)(p1->B * factor + p2->B * factor2);
}

void Blender::Execute()
{
    int x, y, n;
    Pixel *input1, *input2, *output;
    int width = img1->getWidth();
    int height = img1->getHeight();

    //initialize image
    this->img.initialize(width, height);

    //buffers
    input1 = img1->getBuffer();
    input2 = img2->getBuffer();
    output = img.getBuffer();

    //blend images
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            //pixel in output image
            n = (y * width) + x;

            //blend
            blend_pixel(input1 + n, input2 + n, factor, output + n);
        }
    }
}
