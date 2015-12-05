// project/RRA.hpp
// Round Robin Algorithm
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#ifndef RRA_HPP
#define RRA_HPP

// included libraries

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <pthread.h>

#include "DCLL.hpp"
#include "DCLLNode.hpp"
#include "Process.hpp"


using namespace std;

class RRA {
   private:
      // variables
      DCLL * process_list;
      pthread_t adder, scheduler;
      vector<Process> * array_pointer;
      pthread_cond_t schC;
      pthread_mutex_t lock, print;
      int * mrgArr;
      int TQ;

   public:
      RRA(); // constructor
      ~RRA(); // destructor
      DCLL * getList(); // returns process_list
      static void * process_adder(void * process_array); //static function to start a thread for adding jobs to the DCLL
      static void * CPU_scheduler(void * process_array); // static function to start a thread for processing jobs in the DCLL
      void * process_adder_thread(); // thread to add jobs in the DCLL
      void * CPU_scheduler_thread(); // thread to process jobs in the DCLL
      void simulate_RRA(vector<Process> &process_array); // primary funciton that spawns both adder thread and the scheduler thread
      void merge(int arr[], int l, int m, int r);
      void mergeSort(int arr[], int l, int r);

};

#endif // RRA_HPP
