#ifndef FILTER_H
#define FILTER_H

#include "sink.h"
#include "source.h"

class Filter : public Source, public Sink
{
};

class Shrinker : public Filter
{
public:
    void Execute();            //execute shrinker
};

//LR concat filter class
class LRCombine : public Filter
{
public:
    void Execute();
};

class TBCombine : public Filter
{
public:
    void Execute();
};

class Blender : public Filter
{
    double factor;
public:
    void SetFactor(double f);   //set blending factor
    void Execute();            //execute blender
};

#endif
