run: hola
	./hola
hola: Node.o hola.cpp
	g++ -o hola Node.o hola.cpp
Node.o: Node.cpp Node.h
	g++ -c Node.cpp
clean:
	rm -f hola *.o
