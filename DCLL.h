#ifndef DCLL_H
#define DCLL_H

using namespace std; 

#include <ctime>

class Process;
class DCLLNode;

// include libraries

class DCLL {


private:
    DCLLNode * _head, * _tail;
    int _size;


   public:
      // constructors
      DCLL() {
         _size = 0;
         _head = NULL;
         _tail = NULL;
      }

      // destructor
      ~DCLL() {
         _size = 0;
         _head = NULL;
         _tail = NULL;
      }

      void insertNode(Process * data);
      void removeNode(DCLLNode * node);
      int getSize();
      DCLLNode * getHead();
      DCLLNode * getTail();
      long int getTotalTime();
      bool isEmpty();


};

#endif
