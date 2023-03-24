run: test
	./test
test: RiverCrossing.o
	g++ -o test State.o RiverCrossing.o test.cpp
RiverCrossing.o: State.o RiverCrossing.cpp
	g++ -c State.cpp RiverCrossing.cpp 
State.o: State.cpp
	g++ -c State.cpp
clean:
	rm -f test *.o
