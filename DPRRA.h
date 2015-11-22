#ifndef DPRRA_H_INCLUDED
#define DPRRA_H_INCLUDED

#include "DCLL.h"
#include "DCLLNode.h"
#include <vector>
#include <pthread.h>
#include "Process.h"

using namespace std;

class DPRRA {

private:
    DCLL * process_list;
    pthread_t adder, scheduler;
    vector<Process> * array_pointer;  
    pthread_mutex_t lock, print;  	
public:
    DPRRA(); // constructor
    ~DPRRA(); // destructor
    DCLL * getList(); // returns process_list
    static void * process_adder(void * process_array);
    static void * CPU_scheduler(void * process_array);
    void * process_adder_thread(); 
    void * CPU_scheduler_thread(); 
    void simulate_DPRRA(vector<Process> &process_array);
};

#endif // DPRRA_H_INCLUDED
