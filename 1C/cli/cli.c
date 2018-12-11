#include <math330.h>
#include <stdio.h>
#include <stdlib.h>

void Usage(char *progname)
{
    printf("Usage: %s command value\n\n", progname);
    printf("Valid commands are:\tcos, sin, tan, exp, log, arccos, arcsin, arctan\n");
}
int main(int argc, char *argv[])
{
    double (*mathFunction)(double);
    int      foundFunction = 0;

    if (argc != 3)
    {
        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    foundFunction = 1;
    if (strcmp(argv[1], "cos") == 0)
        mathFunction = cos330;
    else if (strcmp(argv[1], "sin") == 0)
        mathFunction = sin330;
    else if (strcmp(argv[1], "tan") == 0)
        mathFunction = tan330;
    else if (strcmp(argv[1], "exp") == 0)
        mathFunction = exp330;
    else if (strcmp(argv[1], "log") == 0)
        mathFunction = log330;
    else if (strcmp(argv[1], "arccos") == 0)
	mathFunction = arccos330;
    else if (strcmp(argv[1], "arcsin") == 0)
	mathFunction = arcsin330;
    else if (strcmp(argv[1], "arctan") == 0)
	mathFunction = arctan330;
    else
        foundFunction = 0;

    if (! foundFunction)
    {
        printf("Invalid command: %s", argv[1]);
        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    double v = atof(argv[2]);
    printf("%f\n", mathFunction(v));
}
