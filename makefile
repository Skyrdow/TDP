run: test
	./test
test: RiverCrossing.o
	g++ -o test State.o RiverCrossing.o FileReader.o test.cpp
RiverCrossing.o: FileReader.cpp State.cpp  RiverCrossing.cpp
	g++ -c State.cpp RiverCrossing.cpp FileReader.cpp
clean:
	rm -f test *.o
