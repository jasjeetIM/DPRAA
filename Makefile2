all:	main2.cpp DoublyCircularLL.o
	g++ -std=c++0x -o main2 main2.cpp DoublyCircularLL.o
debug:	main2.cpp DoublyCircularLL.o
	g++ -std=c++0x -g -o main2 main2.cpp DoublyCircularLL.o
clean:
	rm -f *.o *~ main2 core

DoublyCircularLL.o:	DoublyCircularLL.cpp DoublyCircularLL.hpp
	g++ -std=c++0x -c DoublyCircularLL.cpp
