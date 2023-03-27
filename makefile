run: test
	./test
test: clean
	g++ -o test *.cpp
clean:
	rm -f test *.o
