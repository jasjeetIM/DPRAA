// project/DCLLNODE.hpp
// Doubly Circular Linked List Node
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#ifndef DCLLNODE_HPP
#define DCLLNODE_HPP

// include libraries

#include <cstdlib>
#include <iostream>

#include "Process.hpp"

class DCLLNode {
   private:
      // variables
      DCLLNode *prev, *next;
      int counter;
      Process *data;

   public:
      // function declarations
      DCLLNode();
      DCLLNode * getNext();
      void setNext(DCLLNode * nextNode);
      DCLLNode * getPrevious();
      void setPrevious(DCLLNode * prevNode);
      Process * getData();
      void setData(Process * new_data);
};

#endif // DCLLNODE_HPP
