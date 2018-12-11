#ifndef FILTER_H
#define FILTER_H

#include "sink.h"
#include "source.h"

class Filter : public Source, public Sink
{
public:
    Filter();
    void Update();
};

class Shrinker : public Filter
{
  protected:
    void Execute(); //execute shrinker
};

//LR concat filter class
class LRCombine : public Filter
{
  protected:
    void Execute();
};

class TBCombine : public Filter
{
  protected:
    void Execute();
};

class Blender : public Filter
{
    double factor;

protected:
    void Execute();           //execute blender

  public:
    void SetFactor(double f); //set blending factor
};

#endif
