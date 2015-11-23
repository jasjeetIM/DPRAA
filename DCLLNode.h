#ifndef DCLLNODE_H_INCLUDED
#define DCLLNODE_H_INCLUDED

using namespace std; 

class Process;

class DCLLNode{
private:
    DCLLNode * prev, * next;
int counter;    
Process * data;
public:
    DCLLNode();
    DCLLNode * getNext();
    void setNext(DCLLNode * nextNode);
    DCLLNode * getPrevious();
    void setPrevious(DCLLNode * prevNode);
    Process * getData();
    void setData(Process * new_data);

};

#endif // DCLLNODE_H_INCLUDED
