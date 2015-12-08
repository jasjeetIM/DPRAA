OBJS = main.o DPRRA.o RRA.o DCLL.o DCLLNode.o Process.o
CC = g++ -std=c++0x
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

P3:    $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o P3 -lpthread

main.o: main.cpp Process.hpp DPRRA.hpp
	$(CC) $(CFLAGS) main.cpp

DPRRA.o: DPRRA.hpp DPRRA.cpp Process.hpp DCLL.hpp
	$(CC) $(CFLAGS) DPRRA.cpp -lpthread

RRA.o: RRA.hpp RRA.cpp Process.hpp DCLL.hpp
	$(CC) $(CFLAGS) RRA.cpp -lpthread

DCLL.o: DCLL.hpp DCLL.cpp DCLLNode.hpp
	$(CC) $(CFLAGS) DCLL.cpp

DCLLNode.o: DCLLNode.hpp DCLLNode.cpp
	$(CC) $(CFLAGS) DCLLNode.cpp

Process.o: Process.hpp Process.cpp
	$(CC) $(CFLAGS) Process.cpp

clean:
	\rm *.o P3

tar:
	tar cfv P3.tar main.cpp DPRRA.hpp DPRRA.cpp RRA.hpp RRA.cpp DCLL.hpp DCLL.cpp \
					DCLLNode.hpp DCLLNode.cpp Process.hpp Process.cpp
