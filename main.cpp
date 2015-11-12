#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Process.h"

using namespace std;

#define MAX_CPU_TIME 100  // Maximum CPU time any process can require
#define NUMBER_OF_PROCESSES 10 // Number of processes to create as the input set for performance analysis

void create_processes(vector<Process> & process_array);


int main () {
    srand(time(NULL));   // using a different seed value for random number generator
    vector<Process> process_array;
    create_processes(process_array);

    for (int i = 0; i < process_array.size(); i++)
    {
        cout << "Time required by process " << i << " is: " << process_array[i].get_CPU_time_required() << endl;
    }

    return 0;
}

void create_processes(vector<Process> & process_array) {

    /* Create NUMBER_OF_PROCESSES number of processes, each with a random amount of CPU time required */
    for (int i = 0; i<NUMBER_OF_PROCESSES; i++)
    {
        process_array.push_back(Process(rand()%MAX_CPU_TIME));
    }

}

