#include "DCLLNode.h"
#include <cstdlib>
#include <iostream> 
#include "Process.h"

using namespace std;

DCLLNode::DCLLNode(){
    prev = NULL;
    next = NULL;
    data = NULL;
   counter = 0; 
}



DCLLNode * DCLLNode::getNext(){
    return next;
}

void DCLLNode::setNext(DCLLNode * nextNode){
    next = nextNode;
}

DCLLNode * DCLLNode::getPrevious(){
   return this->prev;
}

void DCLLNode::setPrevious(DCLLNode * prevNode){ 
       counter++; 
        prev = prevNode; 
}

Process * DCLLNode::getData(){
    return data;
}

void DCLLNode::setData(Process * new_data){
    data = new_data;
}
