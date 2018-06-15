#include "PNMreaderCPP.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <fstream>

PNMreaderCPP::PNMreaderCPP(char* path)
{
    //copy file path in new array
    this->file = new char[strlen(path) + 1];
    strcpy(this->file, path);
}

void PNMreaderCPP::Execute()
{
    std::ifstream f_in;
    int width, height, maxval;
    char magicNum[128];

    //read file with read binary mode
    f_in.open(this->file, std::ios::binary | std::ios::in);

    //check if file was opened successfully
    if (!f_in.is_open())
        return;

    //read header of image file
    f_in >> magicNum >> width >> height >> maxval;

    //only work with P6 format currently
    if (strcmp(magicNum, "P6"))
        return;

    //initialize image
    this->img.initialize(width, height);

    // read pixels
    // height * width = num of structs to read
    f_in.seekg(1, std::ios_base::cur);
    f_in.read((char*)this->img.getBuffer(), width * height * 3);

    //close file
    f_in.close();
}
