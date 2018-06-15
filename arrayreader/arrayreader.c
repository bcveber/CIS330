#include <stdio.h>
#include <printf.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	FILE *f_in, *f_out;

	int i;
	int j;

	if (argc != 3){
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");

	int *myArray = malloc(sizeof(int));

	for (i=0; i<5; i++){

		fread(myArray, sizeof(int), 5, f_in);

		for(j=0; j<5; j++){
			fprintf(f_out, "%d\n", myArray[j]);
		}

		fseek(f_in, 5 * sizeof(int), SEEK_CUR);

	}

	fclose(f_in);
	fclose(f_out);
	free(myArray);
}

		

