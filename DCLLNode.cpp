// project/DCLLNODE.cpp
// Doubly Circular Linked List Node
// ----------------------------------------------
// Authors:  Sui Fung Alex Wong, Jasjeet Dhaliwal
// Date:     11/23/2015

#include "DCLLNode.hpp"

DCLLNode::DCLLNode() {
   prev = NULL;
   next = NULL;
   data = NULL;
   counter = 0;
}

DCLLNode * DCLLNode::getNext() {
   return next;
}

void DCLLNode::setNext(DCLLNode * nextNode) {
   next = nextNode;
}

DCLLNode * DCLLNode::getPrevious() {
   return this->prev;
}

void DCLLNode::setPrevious(DCLLNode * prevNode) {
   ++counter;
   prev = prevNode;
}

Process * DCLLNode::getData() {
   return data;
}

void DCLLNode::setData(Process * new_data) {
   data = new_data;
}
