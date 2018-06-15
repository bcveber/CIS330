
#include <prototypes.h>
#include <stdio.h>

int main()
{
    struct Shape shapes[9];
    int i;

    InitializeCircle(shapes+0, 1, 0, 0);
    InitializeCircle(shapes+1, 1.5, 6, 8);
    InitializeCircle(shapes+2, 0.5, -3, 4);

    InitializeRectangle(shapes+3, 0, 1, 0, 1);
    InitializeRectangle(shapes+4, 1, 1.1, 10, 20);
    InitializeRectangle(shapes+5, 1.5, 3.5, 10, 12);

    InitializeTriangle(shapes+6, 0, 1, 0, 1);
    InitializeTriangle(shapes+7, 0, 1, 0, 0.1);
    InitializeTriangle(shapes+8, 0, 10, 0, 50);

    for (i = 0 ; i < 9 ; i++)
    {
        double bbox[4];
        printf("Shape %d\n", i);
        printf("\tArea: %f\n", shapes[i].ft.GetArea(shapes+i));
        shapes[i].ft.GetBoundingBox(shapes+i, bbox);
        printf("\tBbox: %f-%f, %f-%f\n", bbox[0], bbox[1], bbox[2], bbox[3]);
    }
}

