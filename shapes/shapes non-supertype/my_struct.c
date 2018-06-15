/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>

//set up circle structure variables
void InitializeCircle(Circle* obj, double radius, double originX, double originY)
{
    //obj = pointer of structure type
    //access structure members with obj->xxx and set it equal to the initialize value
    //entered from above 
    obj->radius = radius;
    obj->originX = originX;
    obj->originY = originY;
}

//set up rectangle structure variables
void InitializeRectangle(Rectangle* obj, double minX, double maxX, double minY, double maxY)
{
    obj->minX = minX;
    obj->minY = minY;
    obj->maxX = maxX;
    obj->maxY = maxY;
}

//set up triangle structure variables
void InitializeTriangle(Triangle* obj, double pt1X, double pt2X, double minY, double maxY)
{
    obj->pt1X = pt1X;
    obj->pt2X = pt2X;
    obj->minY = minY;
    obj->maxY = maxY;
}

double GetCircleArea(Circle* obj)
{
    //radii will access the struct and get the circles radius
    double radii = obj->radius;
    double area = 3.14159 * radii * radii;
    return area;
}

double GetRectangleArea(Rectangle* obj)
{
    //get maxX and MinX values from struct and subtract to get width
    double width = obj->maxX - obj->minX;

    //get maxY and MinY values from struct to get height
    double height = obj->maxY - obj->minY;
    double area = width * height;

    return area;
}

double GetTriangleArea(Triangle* obj)
{
    //and so on...
    double base = obj->pt2X - obj->pt1X;
    double height = obj->maxY - obj->minY;
    double area = 0.5 * base * height;

    return area;
}

void GetCircleBoundingBox(Circle* obj, double* bbox)
{
    //bbox = pointer to array of bbox objects
    //pull values from the certain struct with obj->xx and store them in bbox
    bbox[0] = obj->originX - obj->radius;
    bbox[1] = obj->originX + obj->radius;
    bbox[2] = obj->originY - obj->radius;
    bbox[3] = obj->originY + obj->radius;
}

void GetRectangleBoundingBox(Rectangle* obj, double* bbox)
{
    bbox[0] = obj->minX;
    bbox[1] = obj->maxX;
    bbox[2] = obj->minY;
    bbox[3] = obj->maxY;
}

void GetTriangleBoundingBox(Triangle* obj, double* bbox)
{
    bbox[0] = obj->pt1X;
    bbox[1] = obj->pt2X;
    bbox[2] = obj->minY;
    bbox[3] = obj->maxY;
}
