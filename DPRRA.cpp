// project/DPRRA.cpp
// Dynamic Priority-based Round Robin Algorithm
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include "DPRRA.hpp"

DPRRA::DPRRA() {
   process_list = new DCLL;
}

DPRRA::~DPRRA() {
   delete process_list;
}

DCLL * DPRRA::getList() {
   return process_list;
}

void * DPRRA::process_adder(void * param) {
   DPRRA *non_static_object = (DPRRA *)param;
   non_static_object->process_adder_thread();
   pthread_exit(0);
}

void * DPRRA::CPU_scheduler(void * param) {
   DPRRA *non_static_object = (DPRRA *)param;
   non_static_object->CPU_scheduler_thread();
   pthread_exit(0);
}

void * DPRRA::process_adder_thread(void) {
   chrono::system_clock::time_point curr;

   pthread_mutex_lock(&lock);
   unsigned int size = array_pointer->size();
   pthread_mutex_unlock(&lock);

   for (unsigned int i = 0; i < size; ++i) {
      curr = chrono::system_clock::now();
      pthread_mutex_lock(&lock);
      (*array_pointer)[i].set_arrival_time(curr);
      process_list->insertNode(&(*array_pointer)[i]);
      pthread_mutex_unlock(&lock);
   }

   cout << "All jobs have been added" << endl;
   return 0;
}

void * DPRRA::CPU_scheduler_thread(void) {
   DCLLNode *temp, *t;
   DCLLNode *CPU = 0;
   bool started = false;
   unsigned int number_of_jobs_completed, list_size, number_of_jobs;
   long int time_quanta, total_time, waiting_time, time_remaining;

   while (CPU == NULL) {
      pthread_mutex_lock(&lock);
      CPU = process_list->getHead();
      pthread_mutex_unlock(&lock);
   }

   number_of_jobs_completed = list_size = 0;

   pthread_mutex_lock(&lock);
   number_of_jobs = array_pointer->size();
   pthread_mutex_unlock(&lock);

   // wait until the list has at least 1 process to start
   while (!started) {
      pthread_mutex_lock(&lock);
      list_size = process_list->getSize();
      pthread_mutex_unlock(&lock);

      if (list_size > 0) {
         started = true;
      }
   }

   // cycling through the list until all jobs are completed
   while (number_of_jobs_completed != number_of_jobs) {
      pthread_mutex_lock(&lock);
      list_size = process_list->getSize();
      pthread_mutex_unlock(&lock);

      if (list_size > 0) { // processing of one job at a time
         pthread_mutex_lock(&lock);
         total_time = process_list->getTotalTime(); // total waiting time for all processes in the list
         waiting_time = CPU->getData()->get_waiting_time();
         cout << "Current Job waiting time is " << waiting_time << endl;

         time_quanta = (waiting_time / total_time) * MAX_TIME_QUANTA;
         time_remaining = CPU->getData()->get_time_remaining() - time_quanta;
         CPU->getData()->set_time_remaining(time_remaining);

         temp = CPU->getNext();
         if (time_remaining <= 0) {
            t = process_list->getHead();
            process_list->removeNode(t);
            ++number_of_jobs_completed;
            CPU = temp;
            cout << number_of_jobs_completed << " jobs have been completed" << endl;
         } else {
            CPU = CPU->getNext();
         }
         pthread_mutex_unlock(&lock);
      }
   }
   cout << "ALL JOBS HAVE BEEN COMPLTED." << endl;
   return 0;
}

void DPRRA::simulate_DPRRA(vector <Process> &process_array) {
   int adder_creation, scheduler_creation;

   pthread_mutex_init(&lock, 0);
   array_pointer = &process_array;
   pthread_mutex_init(&print, 0);

   adder_creation = pthread_create(&adder, 0, &process_adder, this);
   if (adder_creation) {
      cout << "Error: unable to create thread," << adder_creation  << endl;
      exit(-1);
   }

   scheduler_creation = pthread_create(&scheduler, 0, &CPU_scheduler, this);
   if (scheduler_creation) {
      cout << "Error: unable to create thread," << scheduler_creation << endl;
      exit(-1);
   }

   cout << "threads have been joined" << endl;
   pthread_join(adder, 0);
   pthread_join(scheduler, 0);
   cout << "threads have been joined" << endl;
   pthread_mutex_destroy(&lock);
}
