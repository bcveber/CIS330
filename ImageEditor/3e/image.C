#include "image.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "source.h"

int Image::getWidth()
{
    return this->width;
}

int Image::getHeight()
{
    return this->height;
}

int Image::getMaxVal()
{
    //pixel max value
    return this->maxval;
}

Pixel* Image::getBuffer()
{
    //buffer pointer
    return this->buffer;
}

void Image::Destroy()
{
    if (!this->buffer) return;

    delete[] this->buffer;
    this->buffer = 0;
}

//set new image buffer
void Image::initialize(int w, int h)
{
    //destroy already created buffer if any
    Destroy();

    this->buffer = new Pixel[w * h];  //set image buffer
    this->width = w;                 //set image width
    this->height = h;
    this->maxval = 255;
}

void Image::setSource(Source *src)
{
    this->buffer = 0;
    this->source = src;
}

void Image::Update()
{
    if (this->source)
        this->source->Update();
}

void Image::Clean()
{
    if (this->source)
        this->source->Clean();
}
