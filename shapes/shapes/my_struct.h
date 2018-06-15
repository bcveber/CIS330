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

enum ShapeType
{
    Circle,
    Rectangle,
    Triangle
};

union ShapeUnion
{
    struct Circle circle;
    struct Triangle triangle;
    struct Rectangle rectangle;
};

struct Shape;

struct FunctionTable
{
    double (*GetArea)(struct Shape *shape);
    void (*GetBoundingBox)(struct Shape *shape, double *bbox);
};

struct Shape
{
    union ShapeUnion fig;
    enum ShapeType type;
    struct FunctionTable ft;
};
