#include "PNMwriterCPP.h"

#include <iostream>
#include <fstream>

//write image
void PNMwriterCPP::Write(char *file)
{
    char header[50];
    std::ofstream f_out;
    int width, height, maxval;

    //read file with read binary mode
    f_out.open(file, std::ios::binary | std::ios::out);
    if (!f_out.is_open())
        return;

    //get image params
    width = img1->getWidth();
    height = img1->getHeight();
    maxval = img1->getMaxVal();

    //write image header
    sprintf(header, "%s\n%d %d\n%d\n", "P6", width, height, maxval);
    f_out << header;

    //write the elements
    f_out.write((char*)img1->getBuffer(), 3 * width * height);

    //close file
    f_out.close();
}
