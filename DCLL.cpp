// project/DCLL.cpp
// Doubly Circular Linked List
// ----------------------------------------------
// Authors:  Sui Fung Alex Wong, Jasjeet Dhaliwal
// Date:     11/23/2015

#include "DCLL.hpp"

/*
 * This function inserts a node containing a Process into the DCLL.
 *    Complexity: O(1)
 *         Input: data
 *        Output: none
 */
void DCLL::insertNode(Process * data) {
   DCLLNode *node = new DCLLNode();

   node->setData(data);

   if (_size == 0) {
      _head = node;
      _tail = node;
      node->setPrev(_tail);
      node->setNext(_head);
   } else {
      _tail->setNext(node);
      node->setPrev(_tail);
      _tail = node;
      _head->setPrev(_tail);
      _tail->setNext(_head);
   }
   ++_size;
}

/*
 * This function removes a specific node from DCLL.
 *    Complexity: O(1)
 *         Input: node to remove
 *        Output: none
 */
void DCLL::removeNode(DCLLNode * node) {
   DCLLNode *next, *prev;

   if (_size == 0) {
      return;
   } else if (_size == 1) {
      _head = NULL;
      _tail = NULL;
   } else if (_size > 1) {
      prev = node->getPrev();
      next = node->getNext();
      prev->setNext(next);
      next->setPrev(prev);

      if (node == _head) {
         _head = next;
      } else if (node == _tail) {
         _tail = prev;
      }
   }

   delete node;
   --_size;
}

/*
 * This function gets the head of DCLL.
 *    Complexity: O(1)
 *         Input: none
 *        Output: head
 */
DCLLNode * DCLL::getHead() {
   return _head;
}

/*
 * This function gets the tail of DCLL.
 *    Complexity: O(1)
 *         Input: none
 *        Output: tail
 */
DCLLNode * DCLL::getTail() {
   return _tail;
}

/*
 * This function gets the size of DCLL.
 *    Complexity: O(1)
 *         Input: none
 *        Output: size
 */
int DCLL::getSize() {
   return _size;
}

/*
 * This function checks whether DCLL is empty or not.
 *    Complexity: O(1)
 *         Input: none
 *        Output: true if empty, else false
 */
bool DCLL::isEmpty() {
   return _size == 0;
}

/*
 * This function gets the total waiting time of all the processes in the DCLL.
 *    Complexity: O(n)
 *         Input: none
 *        Output: total waiting time
 */
 int DCLL::getTotalTime() {
   DCLLNode *temp = _head;
   int total_time = 0;

   for (int i = 0; i < _size; ++i) {
      total_time += temp->getData()->get_waiting_time();
      temp = temp->getNext();
	}   return total_time;
}
