
#include <my_struct.h>

void InitializeCircle(struct Shape *, double radius, double originX, double originY);
void InitializeRectangle(struct Shape *, double minX, double maxX, double minY, double maxY);
void InitializeTriangle(struct Shape *, double pt1X, double pt2X, double minY, double maxY);

double GetCircleArea(struct Shape *);
double GetRectangleArea(struct Shape *);
double GetTriangleArea(struct Shape *);

void GetCircleBoundingBox(struct Shape *, double *);
void GetRectangleBoundingBox(struct Shape *, double *);
void GetTriangleBoundingBox(struct Shape *, double *);

