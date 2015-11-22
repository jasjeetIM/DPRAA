OBJS = main.o DPRRA.o DCLL.o DCLLNode.o Process.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

TP:    $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o TP -lpthread

main.o: main.cpp Process.h DPRRA.h
	$(CC) $(CFLAGS) main.cpp

DPRRA.o: DPRRA.h DPRRA.cpp Process.h DCLL.h
	$(CC) $(CFLAGS) DPRRA.cpp -lpthread

DCLL.o: DCLL.h DCLL.cpp DCLLNode.h
	$(CC) $(CFLAGS) DCLL.cpp

DCLLNode.o: DCLLNode.h DCLLNode.cpp
	$(CC) $(CFLAGS) DCLLNode.cpp

Process.o: Process.h Process.cpp
	$(CC) $(CFLAGS) Process.cpp 

clean:
	\rm *.o TP

tar:
	tar cfv TP.tar main.cpp DPRRA.h DPRRA.cpp \
                DCLL.h DCLL.cpp DCLLNode.h DCLLNode.cpp Process.h Process.cpp
