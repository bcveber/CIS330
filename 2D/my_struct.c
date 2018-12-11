/* This file should contain the 9 functions defined in prototypes.h */

#include <prototypes.h>
#include <assert.h>

//set up shape struct with circle type
void InitializeCircle(struct Shape * shape, double radius, double originX, double originY)
{
    //create shape type info
    shape->type = Circle;

    //create shape function table
    shape->ft.GetArea = &GetCircleArea;
    shape->ft.GetBoundingBox = &GetCircleBoundingBox;

    //create shape information
    shape->fig.circle.radius = radius;
    shape->fig.circle.originX = originX;
    shape->fig.circle.originY = originY;
}

//set up shape struct with rectangle type
void InitializeRectangle(struct Shape * shape, double minX, double maxX, double minY, double maxY)
{
    //shape type info
    shape->type = Rectangle;

    //shape function table
    shape->ft.GetArea = &GetRectangleArea;
    shape->ft.GetBoundingBox = &GetRectangleBoundingBox;

    //shape information
    shape->fig.rectangle.minX = minX;
    shape->fig.rectangle.minY = minY;
    shape->fig.rectangle.maxX = maxX;
    shape->fig.rectangle.maxY = maxY;
}

//set up shape struct with rectangle type
void InitializeTriangle(struct Shape * shape, double pt1X, double pt2X, double minY, double maxY)
{
    //shape type info
    shape->type = Triangle;

    //shape function table
    shape->ft.GetArea = &GetTriangleArea;
    shape->ft.GetBoundingBox = &GetTriangleBoundingBox;

    //shape information
    shape->fig.triangle.pt1X = pt1X;
    shape->fig.triangle.pt2X = pt2X;
    shape->fig.triangle.minY = minY;
    shape->fig.triangle.maxY = maxY;
}

//calculate circle area from shape info
double GetCircleArea(struct Shape * shape)
{
    //assert shape type
    assert(shape->type == Circle);

    //radii will access the struct and get the circles radius
    double radii = shape->fig.circle.radius;
    double area = 3.14159 * radii * radii;

    return area;
}

//calculate rectangle area from shape info
double GetRectangleArea(struct Shape * shape)
{
    //assert shape type
    assert(shape->type == Rectangle);

    //get maxX and MinX values from struct and subtract to get width
    double width = shape->fig.rectangle.maxX - shape->fig.rectangle.minX;

    //get maxY and MinY values from struct to get height
    double height = shape->fig.rectangle.maxY - shape->fig.rectangle.minY;
    double area = width * height;

    return area;
}

//calculate triangle area from shape information
double GetTriangleArea(struct Shape * shape)
{
    //assert shape type
    assert(shape->type == Triangle);

    //and so on...
    double base = shape->fig.triangle.pt2X - shape->fig.triangle.pt1X;
    double height = shape->fig.triangle.maxY - shape->fig.triangle.minY;
    double area = 0.5 * base * height;

    return area;
}

//calculate circle bounding box from shape info
void GetCircleBoundingBox(struct Shape * shape, double *bbox)
{
    //assert shape type
    assert(shape->type == Circle);

    //calculate bounding box
    //bbox = pointer to array of bbox objects
    //pull values from the certain struct with shape->fig.circle.xx and store them in bbox
    bbox[0] = shape->fig.circle.originX - shape->fig.circle.radius;
    bbox[1] = shape->fig.circle.originX + shape->fig.circle.radius;
    bbox[2] = shape->fig.circle.originY - shape->fig.circle.radius;
    bbox[3] = shape->fig.circle.originY + shape->fig.circle.radius;
}

//calculate rectangle bounding box from shape info
void GetRectangleBoundingBox(struct Shape * shape, double *bbox)
{
    //assert shape type
    assert(shape->type == Rectangle);

    //calculate bounding box
    bbox[0] = shape->fig.rectangle.minX;
    bbox[1] = shape->fig.rectangle.maxX;
    bbox[2] = shape->fig.rectangle.minY;
    bbox[3] = shape->fig.rectangle.maxY;
}

//calculate triangle bounding box from shape info
void GetTriangleBoundingBox(struct Shape * shape, double *bbox)
{
    //assert shape type
    assert(shape->type == Triangle);

    //calculate bounding box
    bbox[0] = shape->fig.triangle.pt1X;
    bbox[1] = shape->fig.triangle.pt2X;
    bbox[2] = shape->fig.triangle.minY;
    bbox[3] = shape->fig.triangle.maxY;
}
