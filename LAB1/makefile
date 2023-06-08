all: test testAVL testFileReader testNode testOperation testState
test: tests/test.cpp RiverCrossing.cpp
	g++ -O2 -o test *.cpp tests/test.cpp
testAVL: 
	g++ -o testAVL *.cpp tests/testAVL.cpp
testFileReader: 
	g++ -o testFileReader *.cpp tests/testFileReader.cpp
testNode: 
	g++ -o testNode *.cpp tests/testNode.cpp
testOperation: 
	g++ -o testOperation *.cpp tests/testOperation.cpp
testState: 
	g++ -o testState *.cpp tests/testState.cpp
