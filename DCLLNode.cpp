#include "DCLLNode.h"
#include <cstdlib>
#include <iostream> 
class Process;

using namespace std;

DCLLNode::DCLLNode(){
    prev = NULL;
    next = NULL;
    data = NULL;
}


DCLLNode * DCLLNode::getNext(){
    return next;
}

void DCLLNode::setNext(DCLLNode * nextNode){
    next = nextNode;
}

DCLLNode * DCLLNode::getPrevious(){
  cout << "Node:  " << this<< " Prev: " << prev  << endl; 
   return prev;
}

void DCLLNode::setPrevious(DCLLNode * prevNode){ 
        prev = prevNode; 
}

Process * DCLLNode::getData(){
    return data;
}

void DCLLNode::setData(Process * new_data){
    data = new_data;
}
