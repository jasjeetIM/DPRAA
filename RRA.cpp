// project/RRA.cpp
// Round Robin Algorithm
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include "RRA.hpp"


/*
 * This is the constructor for a RRA object which contains a DCLL.
 * finish the job.
 *    Complexity: O(1)
 *         Input: none
 *        Output: none
 */
RRA::RRA() {
   process_list = new DCLL;
}

/*
 * This is the destructor for RRA which deletes the DCLL upon being called.
 *    Complexity: O(1)
 *         Input: none
 *        Output: none
 */
RRA::~RRA() {
   delete process_list;
}

/*
 *  This function returns a pointer to the DCLL.
 *         Complexity: O(1)
 *         Input: none
 *        Output: process list
 */
DCLL * RRA::getList() {
   return process_list;
}

/*
 * This static function is executed in a new thread. It then calls the
 * process_adder_thread() function which enables multithreading.
 *    Complexity: O(1)
 *         Input: param
 *        Output: pointer to the thread
 */
void * RRA::process_adder(void * param) {
   RRA *non_static_object = (RRA *)param;
   non_static_object->process_adder_thread();
   pthread_exit(0);
}

/*
 * This static function is executed in a new thread. It then calls the
 * CPU_scheduler_thread() function which enables multithreading.
 *    Complexity: O(1)
 *         Input: param
 *        Output: pointer to the thread
 */
void * RRA::CPU_scheduler(void * param) {
   RRA *non_static_object = (RRA *)param;
   non_static_object->CPU_scheduler_thread();
   pthread_exit(0);
}


/*
 * This is a member function that adds new DCLLNodes to the DCLL. Each node
 * contains a process from the process array that is passed to the
 * simulate_RRA() function.
 *    Complexity: O(n)
 *         Input: none
 *        Output: pointer to the thread
 */
void * RRA::process_adder_thread(void) {
   chrono::system_clock::time_point curr;

   pthread_mutex_lock(&lock);
   unsigned int size = array_pointer->size();
   pthread_mutex_unlock(&lock);

   for (unsigned int i = 0; i < size; ++i) {
      curr = chrono::system_clock::now();
      pthread_mutex_lock(&lock);
      (*array_pointer)[i].set_arrival_time(curr);
      process_list->insertNode(&(*array_pointer)[i]);
      pthread_cond_signal(&schC);
      pthread_mutex_unlock(&lock);
   }

   pthread_mutex_lock(&print);
   cout << "All jobs have been added" << endl;
   pthread_mutex_unlock(&print);
   return 0;
}


/*
 * This is a member function that processes each node in the DCLL using
 * the RRA algorithm. It calculates time_quanta for every node and then
 * processes that node. Once the node has been processed (job has been
 * completed), it then removes that node from the DCLL and marks the completion
 * time in the job (Process).
 *    Complexity: O(1)
 *         Input: none
 *        Output: pointer to the thread
 */
void * RRA::CPU_scheduler_thread(void) {
   DCLLNode *temp, *tempNode;
   DCLLNode *CPU = 0;
   bool started = false;
   unsigned int completed_jobs, list_size, num_jobs;
   float time_remaining;
   chrono::system_clock::time_point completion_time;

   while (CPU == NULL) {
      pthread_mutex_lock(&lock);
      CPU = process_list->getHead();
      pthread_mutex_unlock(&lock);
   }

   completed_jobs = list_size = 0;

   pthread_mutex_lock(&lock);
   num_jobs = array_pointer->size();
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
   while (completed_jobs != num_jobs) {
      pthread_mutex_lock(&lock);
      list_size = process_list->getSize();
      pthread_mutex_unlock(&lock);

      if (list_size > 0) { // processing of one job at a time
         pthread_mutex_lock(&lock);

         time_remaining = CPU->getData()->get_time_remaining() - TIME_QUANTA;
         CPU->getData()->set_time_remaining(time_remaining);
         while (CPU->getNext() == NULL) {
            pthread_cond_wait(&schC, &lock);
         }
         temp = CPU->getNext();

         if (time_remaining <= 0.00) {
            completion_time = chrono::system_clock::now();
            CPU->getData()->set_completion_time(completion_time);
            tempNode = process_list->getHead();
            process_list->removeNode(tempNode);
            ++completed_jobs;
            CPU = temp;

            pthread_mutex_lock(&print);
            cout << completed_jobs << " jobs have been completed" << endl;
            pthread_mutex_unlock(&print);
         } else {
            CPU = CPU->getNext();
         }
         pthread_mutex_unlock(&lock);
      }
   }

   pthread_mutex_lock(&print);
   cout << "ALL JOBS HAVE BEEN COMPLTED." << endl;
   pthread_mutex_unlock(&print);
   return 0;
}


/*
 * This is the primary function that spawns two threads:
 *    a) adder thread
 *    b) scheduler thread.
 * As the name suggests, the adder thread adds jobs to the DCLL and the
 * scheduler thread processes jobs in the DCLL.
 *    Complexity: O(1)
 *         Input: array of processes
 *        Output: none
 */
void RRA::simulate_RRA(vector<Process> &process_array) {
   int adder_creation, scheduler_creation;
   
   pthread_mutex_init(&lock, 0);
   array_pointer = &process_array;
   pthread_mutex_init(&print, 0);
   pthread_cond_init(&schC, 0);

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

   pthread_join(adder, 0);
   pthread_join(scheduler, 0);
   pthread_cond_destroy(&schC);
   pthread_mutex_destroy(&lock);
   pthread_mutex_destroy(&print);
}
