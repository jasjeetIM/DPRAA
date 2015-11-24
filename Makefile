OBJS = main.o RRA.o DPRRA.o DCLL.o DCLLNode.o Process.o
CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

TP:    $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o TP -lpthread

main.o: main.cpp Process.hpp DPRRA.hpp RRA.hpp
	$(CC) $(CFLAGS) main.cpp

RRA.o: RRA.hpp RRA.cpp Process.hpp DCLL.hpp
	$(CC) $(CFLAGS) RRA.cpp -lpthread

DPRRA.o: DPRRA.hpp DPRRA.cpp Process.hpp DCLL.hpp
	$(CC) $(CFLAGS) DPRRA.cpp -lpthread

DCLL.o: DCLL.hpp DCLL.cpp DCLLNode.hpp
	$(CC) $(CFLAGS) DCLL.cpp

DCLLNode.o: DCLLNode.hpp DCLLNode.cpp
	$(CC) $(CFLAGS) DCLLNode.cpp

Process.o: Process.hpp Process.cpp
	$(CC) $(CFLAGS) Process.cpp

clean:
	\rm *.o TP

tar:
	tar cfv TP.tar main.cpp DPRRA.hpp DPRRA.cpp DCLL.hpp DCLL.cpp \
					DCLLNode.hpp DCLLNode.cpp Process.hpp Process.cpp \
					RRA.hpp RRA.cpp
