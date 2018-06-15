#ifndef __SINK_H__
#define __SINK_H__

#include "image.h"

// Sink class
class Sink
{
protected:
    Image *img1, *img2;
public:
    void SetInput(Image *img);     // set first input image
    void SetInput2(Image *img);    // set second input image
};

#endif
