SRC=main3E.C image.C sink.C source.C PNMreader.C PNMwriter.C filter.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3E

.C.o: $<
	g++ -I. -c $<

clean:
	rm *.o proj3E
