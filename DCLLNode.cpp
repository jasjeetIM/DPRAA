// project/DCLLNODE.cpp
// Doubly Circular Linked List Node
// ----------------------------------------------
// Authors:  Sui Fung Alex Wong, Jasjeet Dhaliwal
// Date:     11/23/2015

#include "DCLLNode.hpp"

/*
 * This is the constructor of DCLLNode.
 *    Complexity: O(1)
 *         Input: none
 *        Output: none
 */
DCLLNode::DCLLNode() {
   prev = NULL;
   next = NULL;
   data = NULL;
   counter = 0;
}

/*
 * This function get the next node of this node.
 *    Complexity: O(1)
 *         Input: none
 *        Output: next
 */
DCLLNode * DCLLNode::getNext() {
   return next;
}

/*
 * This function set the next node of this node.
 *    Complexity: O(1)
 *         Input: nextNode
 *        Output: none
 */
void DCLLNode::setNext(DCLLNode * nextNode) {
   next = nextNode;
}

/*
 * This function get the previous node of this node.
 *    Complexity: O(1)
 *         Input: none
 *        Output: prev
 */
DCLLNode * DCLLNode::getPrev() {
   return this->prev;
}

/*
 * This function set the previous node of this node.
 *    Complexity: O(1)
 *         Input: none
 *        Output: next
 */
void DCLLNode::setPrev(DCLLNode * prevNode) {
   prev = prevNode;
   ++counter;
}

/*
 * This function get the data of this node.
 *    Complexity: O(1)
 *         Input: none
 *        Output: data
 */
Process * DCLLNode::getData() {
   return data;
}

/*
 * This function set the data of this node.
 *    Complexity: O(1)
 *         Input: data
 *        Output: none
 */
void DCLLNode::setData(Process * new_data) {
   data = new_data;
}
