#ifndef PNM_READER_H
#define PNM_READER_H

#include "source.h"

class PNMreader : public Source
{
    char *file;
public:
    PNMreader(char* path);        //initialize reader w/ path
    void Execute();               //PNMreader run function
};

#endif
