all: c_example cpp_example

c_example.o: ../simplelogger.h
cpp_example.o: ../simplelogger.h

c_example: c_example.o
	gcc -o c_example c_example.o

cpp_example: cpp_example.o
	g++ -o cpp_example cpp_example.o

clean:
	rm *.o

realclean: clean
	rm c_example cpp_example
