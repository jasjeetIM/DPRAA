// project/main.cpp
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>

#include "DPRRA.hpp"
#include "Process.hpp"

using namespace std;

#define MAX_CPU_TIME 100 // Maximum CPU time any process can require
#define NUMBER_OF_PROCESSES 10 // Number of processes to create as the input set

void create_processes(vector<Process> & process_array);

int main () {
   DPRRA Dynamic_RRA;
   vector<Process> process_array; // vector of processes

   srand(time(NULL)); // using a different seed value for random number generator
   create_processes(process_array); // function that will populate the vector with processes

   cout << "Starting Algorithm" << endl;
   Dynamic_RRA.simulate_DPRRA(process_array);
   cout << "Algorithm has been completed " << endl;

   return 0;
}

void create_processes(vector<Process> & process_array) {
   /* Create NUMBER_OF_PROCESSES number of processes, each with an arbitrary amount of CPU time required */
   for (int i = 0; i<NUMBER_OF_PROCESSES; ++i) {
      typedef std::chrono::duration<long int, ratio<1,1000000000> > nanoseconds;
      nanoseconds p_time(rand() % MAX_CPU_TIME);
      process_array.push_back(Process(std::chrono::duration_cast<nanoseconds>(p_time).count()));
    }
}
