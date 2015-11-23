// project/DoublyCircularLL.hpp
// Doubly Circular Linked List
// ---------------------------
// Author:  Sui Fung Alex Wong
// Date:    11/13/2015

#ifndef DOUBLYCIRCULARLL_H
#define DOUBLYCIRCULARLL_H

#include <cstdlib>
#include "Process.h"

// include libraries

class DoublyCircularLL {
   public:
      // constructors
      DoublyCircularLL() {
         _size = 0;
         _head = NULL;
         _tail = NULL;
         _curr = NULL;
      }

      // destructor
      ~DoublyCircularLL() {
         _size = 0;
         _head = NULL;
         _tail = NULL;
         _curr = NULL;
      }

      void insert(Process * data);
      void remove();
      bool stepNext();
      void * getCurrent();
      int size();
      bool empty();

   private:
      struct DCLLNode {
         Process * data;
         DCLLNode * prev;
         DCLLNode * next;
      };

      // variables
      int _size;
      DCLLNode *_head, *_tail, *_curr;
};

#endif
