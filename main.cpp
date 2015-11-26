// project/main.cpp
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>

#include "RRA.hpp"
#include "DPRRA.hpp"
#include "Process.hpp"

using namespace std;

#define MAX_CPU_TIME 40 // Maximum CPU time any process can require
#define NUMBER_OF_PROCESSES 10 // Number of processes to create as the input set

void create_processes(vector<Process> & processes);

int main () {
   DPRRA Dynamic_RRA;
   RRA trad_RRA;
   vector<Process> processes;

   srand(time(NULL)); // using a different seed value for random number generator
   create_processes(processes); // function that will populate the vector with processes

   cout << "Starting Dynamic Priority-based Round Robin Algorithm" << endl;
   Dynamic_RRA.simulate_DPRRA(processes);
   cout << "Dynamic Priority-based Round Robin Algorithm has been completed";

   cout << endl << endl << "Starting Round Robin Algorithm" << endl;
   trad_RRA.simulate_RRA(processes);
   cout << "Round Robin Algorithm has been completed" << endl;

   return 0;
}

/*
 * This function create NUMBER_OF_PROCESSES number of processes, each with an
 * arbitrary amount of CPU time required, and put it into the input vector.
 *    Complexity: O(1)
 *         Input: vector of processes
 *        Output: none
 */
void create_processes(vector<Process> & processes) {
   for (int i = 0; i < NUMBER_OF_PROCESSES; ++i) {
      typedef chrono::duration<long int, ratio<1,1000000000>> nsec;
      nsec p_time(rand() % MAX_CPU_TIME);
      processes.push_back(Process(chrono::duration_cast<nsec>(p_time).count()));
   }
}
