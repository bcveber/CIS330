
project_2D: driver_2D.o my_struct.o
	gcc -o project_2D my_struct.o driver_2D.o

driver_2D.o: driver_2D.c prototypes.h my_struct.h
	gcc -c -I. driver_2D.c

my_struct.o: driver_2D.c prototypes.h my_struct.h
	gcc -c -I. my_struct.c

clean:
	rm -f *.o
