// project/DPRRA.hpp
// Dynamic Priority-based Round Robin Algorithm
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#ifndef DPRRA_HPP
#define DPRRA_HPP

// included libraries

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <pthread.h>

#include "DCLL.hpp"
#include "DCLLNode.hpp"
#include "Process.hpp"

#define MAX_TIME_QUANTA 5

using namespace std;

class DPRRA {
   private:
      // variables
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

#endif // DPRRA_HPP
