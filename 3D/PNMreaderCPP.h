#ifndef PNM_READER_H
#define PNM_READER_H

#include "source.h"

class PNMreaderCPP : public Source
{
    char *file;
public:
    PNMreaderCPP(char* path);        //initialize reader w/ path
    void Execute();               //PNMreaderCPP run function
};

#endif
