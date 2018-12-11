#SOURCES: 
#http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#https://www.ibm.com/support/knowledgecenter/en/ssw_aix_61/com.ibm.aix.cmds1/ar.htm#ar__row-d3e27544 
#http://www.puxan.com/web/howto-write-generic-makefiles/ 
#https://stackoverflow.com/questions/4134764/how-to-define-several-include-path-in-makefile 
#https://www.cs.colostate.edu/~cs157/LectureMakefile.pdf

#compile with gcc
CC = gcc

#g adds debug info, wall adds compiler warnings
CFLAGS = -g -Wall

#create lib, bin, include directory variables
DIR_LIB = lib
DIR_BIN = bin
DIR_INCLUDE = include

#AR will replace a file if it already appears in the library
AR = ar
AR_FLAGS = r

#get the object file names from source code names
SOURCES = cos330.o sin330.o tan330.o exp330.o log330.o arccos330.o arcsin330.o arctan330.o

#add bin to the path of trig/exp functions
OBJECTS = $(addprefix $(DIR_BIN)/, $(SOURCES))

#make all rule (makes the program bin/cli from #1 on PDF)
all: $(DIR_BIN)/cli

#make rule to setup include/lib directories, copies header into include directory
$(DIR_INCLUDE):
	#make directory for lib
	mkdir -p $(DIR_LIB)
	
	#make directory for include
	mkdir -p $(DIR_INCLUDE)

	#copy math330.h into include
	cp math330.h $(DIR_INCLUDE)/math330.h

#make rule to build libmath330.a
lib: $(DIR_INCLUDE) $(SOURCES)

	#create the static library libmath330.a and add AR flags
	$(AR) $(AR_FLAGS) libmath330.a $(OBJECTS)

	#add libmath330.a into lib
	cp libmath330.a $(DIR_LIB)/libmath330.a
	
	#add AR flags
	$(AR) $(AR_FLAGS) libmath330.a $(OBJECTS)

#make rule to create cli
$(DIR_BIN)/cli: $(DIR_BIN)/cli.o lib
	
	#create cli
	#gcc -c, source code path is include lib bin/cli.o, output file name/location will be bin/cli
	$(CC) $(CFLAGS) -I$(DIR_INCLUDE) -L$(DIR_LIB) $(DIR_BIN)/cli.o -lmath330 -lm -o $(DIR_BIN)/cli

#make rule to compile and move object files to bin directory
$(DIR_BIN)/cli.o: cli/cli.c $(DIR_INCLUDE)
	#create bin directory
	mkdir -p $(DIR_BIN)

	#gcc -c, source code path is include cli/cli.c, output file name/location will be bin/cli.o
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) cli/cli.c -o $(DIR_BIN)/cli.o

cos330.o: trig/cos330.c $(DIR_INCLUDE)
	#create bin directory
	mkdir -p $(DIR_BIN)
	
	#create the object file for cos function
	#gcc -c, source code path is include trig/cos330.c, output file name/location will be bin/cos330.o
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) trig/cos330.c -o $(DIR_BIN)/cos330.o

sin330.o: trig/sin330.c $(DIR_INCLUDE)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) trig/sin330.c -o $(DIR_BIN)/sin330.o

tan330.o: trig/tan330.c $(DIR_INCLUDE)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) trig/tan330.c -o $(DIR_BIN)/tan330.o

exp330.o: exp/exp330.c $(DIR_INCLUDE)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) exp/exp330.c -o $(DIR_BIN)/exp330.o

log330.o: exp/log330.c $(DIR_INCLUDE)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) exp/log330.c -o $(DIR_BIN)/log330.o

arccos330.o: trig/arccos330.c $(DIR_INCLUDE)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) trig/arccos330.c -o $(DIR_BIN)/arccos330.o

arcsin330.o: trig/arcsin330.c $(DIR_INCLUDE)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) trig/arcsin330.c -o $(DIR_BIN)/arcsin330.o

arctan330.o: trig/arctan330.c $(DIR_INCLUDE)
	mkdir -p $(DIR_BIN)
	$(CC) $(CFLAGS) -c -I$(DIR_INCLUDE) trig/arctan330.c -o $(DIR_BIN)/arctan330.o

#make rule to cleanup everything
clean:
	rm -rf $(DIR_BIN) $(DIR_INCLUDE) $(DIR_LIB)
