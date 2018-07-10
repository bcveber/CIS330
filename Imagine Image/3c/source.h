#ifndef SOURCE_H
#define SOURCE_H

#include "image.h"

class Source
{
protected:
    Image img;
public:
    virtual void Execute() = 0;                 //run source operation
    Image* GetOutput();			//get source image buffer
};

#endif
