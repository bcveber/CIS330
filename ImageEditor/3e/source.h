#ifndef SOURCE_H
#define SOURCE_H

#include "image.h"

class Source
{
protected:
    Image img;
    virtual void Execute() = 0;                //run source operation

public:
    Image* GetOutput();			//get source image buffer
    virtual void Update() = 0;  //run update operation
    void Clean() { img.Destroy(); }
};

#endif
