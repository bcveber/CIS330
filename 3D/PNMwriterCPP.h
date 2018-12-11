#ifndef PNM_WRITER_H
#define PNM_WRITER_H

#include "sink.h"

class PNMwriterCPP : public Sink
{
public:
    void Write(char *path);         //write image
};

#endif
