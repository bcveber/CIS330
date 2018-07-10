#ifndef __SOURCE_H__
#define __SOURCE_H__

#include "image.h"

// Source class
class Source
{
protected:
    Image img;
public:
    virtual void Execute() = 0;    // execute source operation
    Image* GetOutput();            // get source image buffer
};

#endif
