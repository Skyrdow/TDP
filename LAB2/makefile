FLAGS = -g

all: parser

parser: AST.cpp Node.o Node_Operation.o Node_Variable.o Node_Number.o
	g++ $(FLAGS) -o parser Node.o Node_Operation.o Node_Variable.o Node_Number.o AST.cpp

Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp

Node_Operation.o: Node_Operation.cpp Node_Operation.h
	g++ $(FLAGS) -c Node_Operation.cpp

Node_Variable.o: Node_Variable.cpp Node_Variable.h
	g++ $(FLAGS) -c Node_Variable.cpp

Node_Number.o: Node_Number.cpp Node_Number.h
	g++ $(FLAGS) -c Node_Number.cpp

clean:
	rm -f parser *.o
