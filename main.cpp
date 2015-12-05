// project/main.cpp
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>

#include "RRA.hpp"
#include "DPRRA.hpp"
#include "Process.hpp"

using namespace std;

#define MAX_CPU_TIME 40 // Maximum CPU time any process can require
#define NUMBER_OF_PROCESSES 25 // Number of processes to create as the input set

void create_processes(vector<Process> & processes, int maxTime, int numProcess);
void reset_processes(vector<Process> processes, int numProcess);
void print_data_RRA(vector<Process> processes, int numProcess);
void print_data_DPRRA(vector<Process> processes, int numProcess);

int main (int argc, char *argv[]) {
   DPRRA Dynamic_RRA;
   RRA trad_RRA;
   vector<Process> processes;
   int maxTime, numProcess;

   if (argc == 3) {
      maxTime = atoi(argv[1]);
      numProcess = atoi(argv[2]);
   } else {
      maxTime = MAX_CPU_TIME;
      numProcess = NUMBER_OF_PROCESSES;
   }

   srand(time(NULL));
   create_processes(processes, maxTime, numProcess);

   cout << "Starting Dynamic Priority-based Round Robin" << endl;
   Dynamic_RRA.simulate_DPRRA(processes);
   cout << "Dynamic Priority-based Round Robin has been completed" << endl;
   print_data_DPRRA(processes, numProcess);

   reset_processes(processes, numProcess);

   cout << endl << endl << "Starting Round Robin" << endl;
   trad_RRA.simulate_RRA(processes);
   cout << "Round Robin has been completed" << endl;
   print_data_RRA(processes, numProcess);

   return 0;
}

/*
 * This function create NUMBER_OF_PROCESSES number of processes, each with an
 * arbitrary amount of CPU time required, and put it into the input vector.
 *    Complexity: O(n)
 *         Input: vector of processes
 *        Output: none
 */
void create_processes(vector<Process> & processes, int maxTime, int numProcess) {
   int t = 0;

   for (int i = 0; i < numProcess; ++i) {
      t = (rand() % maxTime);
      processes.push_back(Process(t, i));
   }
}

/*
 * This function resets the parameter for the processes.
 *    Complexity: O(n)
 *         Input: vector of processes
 *        Output: none
 */
void reset_processes(vector<Process> processes, int numProcess) {
   for (int i = 0; i < numProcess; ++i) {
      processes[i].reset_data();
   }
}

/*
 * This function prints the data output for DPRRA.
 *    Complexity: O(n)
 *         Input: vector of processes
 *        Output: none
 */
void print_data_DPRRA(vector<Process> processes, int numProcess) {
   double avg_ft, l2_norm, avg_cs, avg_tp;
   unsigned int sum_cs;
   long int sum_ft, sum_l2, ft;
   ofstream Results("DPRRAResults.csv");

   if (Results.is_open()) {
      Results << "Job ID" << ";" << "Flow Time" << ";" << "Context Switches" << endl;
   } else {
      cout << "Unable to open file" << endl;
   }

   sum_ft = sum_l2 = sum_cs = 0;
   for (int i = 0; i < numProcess; ++i) {
      ft = processes[i].get_completion_time().time_since_epoch().count() - processes[i].get_arrival_time().time_since_epoch().count();
      if (Results.is_open()) {
         Results << processes[i].get_id() << ";" << ft << ";" << processes[i].get_cs_count() << endl; // debug printing
      }

      sum_ft += ft;
      sum_l2 += pow(ft, 2.0);
      sum_cs += processes[i].get_cs_count();
   }

   Results.close();

   // average flow time (turnaround time)
   avg_ft = sum_ft / (double) numProcess;
   cout << "         total flow time = " << sum_ft << endl; // debug printing
   cout << "       average flow time = " << avg_ft << endl;

   // L2-norm flow time
   l2_norm = sqrt(sum_l2);
   cout << "      total l2-norm time = " << sum_l2 << endl; // debug printing
   cout << "       l2-norm flow time = " << l2_norm << endl;

   // average context switches
   avg_cs = sum_cs / (double) numProcess;
   cout << "average context switches = " << avg_cs << endl;

   // average throughput
   avg_tp = (double) numProcess / sum_ft;
   cout << "      average throughput = " << avg_tp << endl;
}

/*
 * This function prints the data output for RRA.
 *    Complexity: O(n)
 *         Input: vector of processes
 *        Output: none
 */
void print_data_RRA(vector<Process> processes, int numProcess) {
   double avg_ft, l2_norm, avg_cs, avg_tp;
   unsigned int sum_cs;
   long int sum_ft, sum_l2, ft;
   ofstream Results("RRAResults.csv");

   if (Results.is_open()) {
      Results << "Job ID" << ";" << "Flow Time" <<";" <<  "Context Switches" << endl;
   } else {
      cout << "Unable to open file" << endl;
   }

   sum_ft = sum_l2 = sum_cs = 0;
   for (int i = 0; i < numProcess; ++i) {
      ft = processes[i].get_completion_time().time_since_epoch().count() - processes[i].get_arrival_time().time_since_epoch().count();
      if (Results.is_open()) {
         Results << processes[i].get_id() << ";" << ft << ";" << processes[i].get_cs_count() << endl; // debug printing
      }

      sum_ft += ft;
      sum_l2 += pow(ft, 2.0);
      sum_cs += processes[i].get_cs_count();
   }

   Results.close();

   // average flow time (turnaround time)
   avg_ft = sum_ft / (double) numProcess;
   cout << "         total flow time = " << sum_ft << endl; // debug printing
   cout << "       average flow time = " << avg_ft << endl;

   // L2-norm flow time
   l2_norm = sqrt(sum_l2);
   cout << "      total l2-norm time = " << sum_l2 << endl; // debug printing
   cout << "       l2-norm flow time = " << l2_norm << endl;

   // average context switches
   avg_cs = sum_cs / (double) numProcess;
   cout << "average context switches = " << avg_cs << endl;

   // average throughput
   avg_tp = (double) numProcess / sum_ft;
   cout << "      average throughput = " << avg_tp << endl;
}
