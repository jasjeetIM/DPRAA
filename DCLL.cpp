// project/DCLL.cpp
// Doubly Circular Linked List
// ---------------------------
// Author:  Sui Fung Alex Wong
// Date:    11/13/2015
// edited by Jay: 11/21/2015

#include "DCLL.h"
#include "DCLLNode.h"
#include <ctime>
#include "Process.h"
#include <iostream> 


void DCLL::insertNode(Process * data) {
   DCLLNode * node = new DCLLNode();
   node->setData(data); 
   if (_size == 0) {
      _head = node;
      _tail = node;
      node->setPrevious(_tail); 
      node->setNext(_head);   		  
   } 
   else{
      _tail->setNext(node);
      node->setPrevious(_tail); 
      _tail = node; 
      _head->setPrevious(_tail);  
      _tail->setNext(_head);     
  }
   ++_size;
}

void DCLL::removeNode(DCLLNode * node_to_remove) {
   DCLLNode * node = node_to_remove;
	DCLLNode * nxt, * prv; 
   if (_size == 0) {
      return;
   }

   else if (_size == 1) {
      cout << "size is 1" <<endl;
	_head = NULL;
      _tail = NULL;
   }

   else {
	cout << "size is greater than 1" <<endl;
      prv = node->getPrevious(); 
      nxt = node->getNext(); 
	cout << prv << " and " << nxt << endl;
	prv->setNext(nxt);
        nxt->setPrevious(prv);
   }

   delete node;
   --_size;
}

DCLLNode * DCLL::getHead()
{
    return _head;
}

DCLLNode * DCLL::getTail()
{
    return _tail;
}

int DCLL::getSize() {
   return _size;
}

bool DCLL::isEmpty() {
   return _size == 0;
}

long int DCLL::getTotalTime()
{
    DCLLNode * temp = _head;
    long int total_time;

    for (int i = 0; i< _size; i++)
    {
        total_time+=temp->getData()->getWaitingTime();
        temp=temp->getNext();
	}

    delete temp;
    return total_time;
}
