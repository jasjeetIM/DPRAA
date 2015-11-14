// project/DoublyCircularLL.cpp
// Doubly Circular Linked List
// ---------------------------
// Author:  Sui Fung Alex Wong
// Date:    11/13/2015

#include "DoublyCircularLL.hpp"

void DoublyCircularLL::insert(void * data) {
   DCLLNode * node = new DCLLNode();
   node->data = data;
   node->prev = _tail;
   node->next = _head;

   if (_size == 0) {
      _head = node;
      _tail = node;
      _curr = node;
   } else {
      _tail->next = node;
      _head->prev = node;
      _tail = node;
   }

   ++_size;
}

void DoublyCircularLL::remove() {
   DCLLNode * node = _curr;

   if (_size == 0) {
      return;
   } else if (_size == 1) {
      _head = NULL;
      _tail = NULL;
      _curr = NULL;
   } else {
      node->prev->next = node->next;
      node->next->prev = node->prev;
      _curr = _curr->next;
   }

   delete node;
   --_size;
}

bool DoublyCircularLL::stepNext() {
   if (_size <= 1) {
      return false;
   }

   _curr = _curr->next;
   return true;
}

void * DoublyCircularLL::getCurrent() {
   if (_size == 0) {
      return NULL;
   }

   return _curr->data;
}

int DoublyCircularLL::size() {
   return _size;
}

bool DoublyCircularLL::empty() {
   return _size == 0;
}
