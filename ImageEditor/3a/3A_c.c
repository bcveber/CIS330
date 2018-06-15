#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct
{
    char R;
    char G;
    char B;
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

//reads the PNM/P6 file, returns an image struct
Image *
ReadImage(const char *filename)
{
    FILE *f_in;
    Image *img;
    char magicNum[128];

    //read file with read binary mode
    f_in = fopen(filename, "rb");

    //check if file was opened successfully
    if (!f_in)
    {
        return NULL;
    }

    //give data for image structure
    img = (Image*)malloc(sizeof(Image));

    //read header of image file
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &img->width, &img->height, &img->maxval);

    //only work with P6 format currently
    if (strcmp(magicNum, "P6"))
    {
        //if it isn't P6 then free memory and exit
        free(img);
        return NULL;
    }

    //read image pixel data
    //bytes = width * height
    img->data = (Pixel*)malloc(img->height * img->width * sizeof(Pixel));

    //read pixels
    //height * width = num of structs to read
    fread(img->data, sizeof(Pixel), (img->height * img->width), f_in);

    //return image struct
    return img;
}

//write image
int WriteImage(Image *img, const char *filename)
{
    FILE *f_in;

    //read file with read binary mode
    f_in = fopen(filename, "wb");

    //write image header
    fprintf(f_in, "%s\n%d %d\n%d\n", "P6", img->width, img->height, img->maxval);

    //write the elements
    fwrite(img->data, sizeof(Pixel), (img->width * img->height), f_in);

    return 0;
}

//add yellow diagonal to image
Image *
YellowDiagonal(Image *input)
{
    int x, y, n;
    Image *output;
    Pixel yellow;
    int width = input->width;
    int height = input->height;

    //allocate new image structure
    output = (Image*)malloc(sizeof(Image));
    output->width = width;
    output->height = height;
    output->maxval = input->maxval;
    output->data = (Pixel*)malloc(width * height * sizeof(int));

    //yellow = 255/255/00 aka 0xff/0xff/0x00
    yellow.R = 0xff;
    yellow.G = 0xff;
    yellow.B = 0x00;

    //loop over image and add yellow color to the diagonal
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
	    //get pixel offset
            n = y * width + x;

            //get color info
            Pixel color = input->data[n];
            if (x == y)
            {
                //put yellow pixel there
                color = yellow;
            }

            //write image data
            output->data[n] = color;
        }
    }

    //return new image
    return output;
}

int main(int argc, char *argv[])
{

    //get file names
    const char* f_in = argv[1];
    const char* f_out = argv[2];

    //read image
    Image *img = ReadImage(f_in);

    //add the yellow line
    Image* output = YellowDiagonal(img);

    //write image to output file
    WriteImage(output, f_out);

    //free input image memory
    free(img->data);
    free(img);

    //return success
    return 0;
}
