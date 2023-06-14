FLAGS = -g

all: auto_txts.o main.o testNodeNumber.o testNodeOperation.o testNodeVariable.o testloadFile.o

testloadFile.o: testloadFile.cpp Node.o Node_Operation.o Node_Variable.o Node_Number.o loadFile.o
	g++ $(FLAGS) -o testloadFile.o testloadFile.cpp Node.o Node_Operation.o Node_Variable.o Node_Number.o loadFile.o

testNodeNumber.o: testNodeNumber.cpp Node.o Node_Number.o
	g++ $(FLAGS) -o testNodeNumber.o Node.o Node_Number.o testNodeNumber.cpp

testNodeOperation.o: testNodeOperation.cpp Node.o Node_Number.o
	g++ $(FLAGS) -o testNodeOperation.o Node.o Node_Number.o Node_Operation.o testNodeOperation.cpp

testNodeVariable.o: testNodeVariable.cpp Node.o Node_Variable.o
	g++ $(FLAGS) -o testNodeVariable.o Node.o Node_Variable.o testNodeVariable.cpp

main.o: main.cpp AST.o Node.o Node_Operation.o Node_Variable.o Node_Number.o loadFile.o
	g++ $(FLAGS) -o main.o Node.o Node_Operation.o Node_Variable.o Node_Number.o loadFile.o AST.o main.cpp

auto_txts.o: auto_txts.cpp AST.o Node.o Node_Operation.o Node_Variable.o Node_Number.o loadFile.o
	g++ $(FLAGS) -o auto_txts.o Node.o Node_Operation.o Node_Variable.o Node_Number.o loadFile.o AST.o auto_txts.cpp

AST.o: AST.cpp AST.h
	g++ $(FLAGS) -c AST.cpp

Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp

Node_Operation.o: Node_Operation.cpp Node_Operation.h
	g++ $(FLAGS) -c Node_Operation.cpp

Node_Variable.o: Node_Variable.cpp Node_Variable.h
	g++ $(FLAGS) -c Node_Variable.cpp

Node_Number.o: Node_Number.cpp Node_Number.h
	g++ $(FLAGS) -c Node_Number.cpp

loadFile.o: loadFile.cpp loadFile.h
	g++ $(FLAGS) -c loadFile.cpp

clean:
	rm -f parser *.o
