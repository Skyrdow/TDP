FLAGS = -g
all: main test_Simplex

test_Simplex: Simplex.o BnB.o Heap.o Node.o test_Simplex.cpp
	g++ $(FLAGS) Simplex.o BnB.o test_Simplex.cpp -o test_Simplex Node.o Heap.o
main: Simplex.o BnB.o Heap.o Node.o main.cpp
	g++ $(FLAGS) Simplex.o BnB.o main.cpp -o main Node.o Heap.o
BnB.o: BnB.cpp
	g++ $(FLAGS) -c BnB.cpp
Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp
Heap.o: Heap.cpp Heap.h
	g++ $(FLAGS) -c Heap.cpp
Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp
clean:
	rm -f *.o main test_Simplex
