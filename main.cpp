// project/main.cpp
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include "RRA.hpp"
#include "DPRRA.hpp"
#include "Process.hpp"

using namespace std;

#define MAX_CPU_TIME 1 // Maximum CPU time any process can require
#define NUMBER_OF_PROCESSES 1 // Number of processes to create as the input set

void create_processes(vector<Process> & processes, int maxTime, int numProcess);
void reset_processes(vector<Process> & processes, int numProcess);
void save_data(vector<Process> processes, int numProcess, ofstream & file, float tq);


int main (int argc, char *argv[]) {
   DPRRA Dynamic_RRA;
   RRA trad_RRA;
   vector<Process> processes;
   ofstream DPRRAFile("output/DPRRAResults.csv");
   ofstream RRAFile("output/RRAResults.csv");
   int maxTime, numProcess, j;
   int counter = 0;

   if (DPRRAFile.is_open()) {
      DPRRAFile << "#Processes;Avg_FT_DPRRA;l2Norm_DPRRA;Avg_CS_DPRRA;Avg_TP_DPRRA;Avg_TQ_DPRRA\n";
   } else {
      cout << "Error in opening file.\n";
   }

   if (RRAFile.is_open()) {
      RRAFile << "#Processes;Avg_FT_RRA;l2Norm_RRAAvg_CS_RRA;Avg_TP_RRA;Avg_TQ_RRA\n";
   } else {
      cout << "Error in opening file.\n";
   }

   if (argc == 3) {
      maxTime = atoi(argv[1]);
      numProcess = atoi(argv[2]);
   } else {
      maxTime = MAX_CPU_TIME;
      numProcess = NUMBER_OF_PROCESSES;
   }

   for (int i = 1; i <= 5000; i += 5) {
      j = i * 5;
      maxTime = MAX_CPU_TIME * i;
      numProcess = NUMBER_OF_PROCESSES * j;

      srand(time(NULL));
      create_processes(processes, maxTime, numProcess);
      cout << "Starting Dynamic Priority-based Round Robin\n";
      Dynamic_RRA.simulate_DPRRA(processes);
      cout << "Dynamic Priority-based Round Robin has been completed\n";
      save_data(processes, numProcess, DPRRAFile, Dynamic_RRA.get_avg_tq());

      reset_processes(processes, numProcess);

      cout << endl << endl << "Starting Round Robin\n";
      trad_RRA.simulate_RRA(processes);
      cout << "Round Robin has been completed\n";
      save_data(processes, numProcess, RRAFile, trad_RRA.get_tq());
      processes.clear();
      ++counter;
   }

   DPRRAFile.close();
   RRAFile.close();
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
   for (int i = 0; i < numProcess; ++i) {
      processes.push_back(Process(rand() % maxTime, i));
   }
}

/*
 * This function resets the parameter for the processes.
 *    Complexity: O(n)
 *         Input: vector of processes
 *        Output: none
 */
void reset_processes(vector<Process> & processes, int numProcess) {
   for (int i = 0; i < numProcess; ++i) {
      processes[i].reset_data();
   }
}

/*
 * This function prints the data output.
 *    Complexity: O(n)
 *         Input: vector of processes
 *        Output: none
 */
void save_data(vector<Process> processes, int numProcess,ofstream & outfile, float avg_tq) {
   double avg_ft, l2_norm, avg_cs, avg_tp;
   unsigned int sum_cs;
   long int sum_ft, sum_l2, ft;
   string result;

   sum_ft = sum_l2 = sum_cs = 0;
   for (int i = 0; i < numProcess; ++i) {
      ft = processes[i].get_completion_time().time_since_epoch().count() - processes[i].get_arrival_time().time_since_epoch().count();

      sum_ft += ft;
      sum_l2 += pow(ft, 2.0);
      sum_cs += processes[i].get_cs_count();
   }

   // average flow time (turnaround time)
   avg_ft = sum_ft / (double) numProcess;
   // cout << "         total flow time = " << sum_ft << endl;
   // cout << "       average flow time = " << avg_ft << endl;

   // L2-norm flow time
   l2_norm = sqrt(sum_l2);
   // cout << "      total l2-norm time = " << sum_l2 << endl;
   // cout << "       l2-norm flow time = " << l2_norm << endl;

   // average context switches
   avg_cs = sum_cs / (double) numProcess;
   // cout << "average context switches = " << avg_cs << endl;

   // average throughput
   avg_tp = (double) numProcess / sum_ft;
   // cout << "      average throughput = " << avg_tp << endl;

   if (outfile.is_open()) {
      outfile  << numProcess << ";" << avg_ft << ";" << l2_norm << ";" << avg_cs << ";" << avg_tp << ";" << avg_tq << endl;
   } else {
      cout << "Unable to open File.\n";
   }
}
