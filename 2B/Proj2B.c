#include <stdio.h>
#include <printf.h>
#include <stdlib.h>

//argc: how many command line arguments
//argv: an array containing each of the arguments
int main(int argc, char *argv[]){

	//create file names for our read and write files
	FILE *f_in, *f_out;

	//create incrementer variables
	int i;
	int j;

	//If there aren't exactly two files in command line input, then terminate
	if (argc != 3){
		printf("Usage: %s <file1> <file2>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	//opens the file to be read (argv[1]) and file to be written onto (argv[2])
	f_in = fopen(argv[1], "r");
	f_out = fopen(argv[2], "w");

	//allocate heap space to store values in myArray that will be read from f_in
	int *myArray = malloc(sizeof(int));

	//this loop will go through the first 5 lines of the array we are supposed to 		//extract
	for (i=0; i<5; i++){

		//read the first 5 integers made possible by denoting size (sizeof(int)) 		//so it can identify the 5 integers, read from f_in and send values to 			//myArray
		fread(myArray, sizeof(int), 5, f_in);


	//go through the 5 values stored/"teed up" in myArray memory, and export 		//them to our destination/write file (f_out) via indexing
		for(j=0; j<5; j++){
			fprintf(f_out, "%d\n", myArray[j]);
		}

		//seek from the binary file "f_in", start at where the read left off
		//which is SEEK_CUR, then skip the rest of the ints in the array that
		//we are supposed to ignore denoted by (5 * sizeof(int))
		fseek(f_in, 5 * sizeof(int), SEEK_CUR);

	}

	//close our read and write files
	fclose(f_in);
	fclose(f_out);

	//free up heap space by getting rid of myArray
	free(myArray);
}

		

