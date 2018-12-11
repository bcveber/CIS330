/* This file should contain your struct definitions for Circle, Triangle, and
   Rectangle */

struct Circle
{

    double radius;
    double originX;
    double originY;
};

struct Triangle
{
    double pt1X;
    double pt2X;
    double minY;
    double maxY;
};

struct Rectangle
{
    double minX;
    double minY;
    double maxX;
    double maxY;
};

//type of shapes available
enum ShapeType
{
    Circle,
    Rectangle,
    Triangle
};

//holds shape structures
union ShapeUnion
{
    struct Circle circle;
    struct Triangle triangle;
    struct Rectangle rectangle;
};

//need this beforehand for compiler
struct Shape;

//pointer to functions that can be called on these shapes
struct FunctionTable
{
    double (*GetArea)(struct Shape *shape);
    void (*GetBoundingBox)(struct Shape *shape, double *bbox);
};

//shape structure w/ shape union, shape type, and functiontable
struct Shape
{
    union ShapeUnion fig;
    enum ShapeType type;
    struct FunctionTable ft;
};
