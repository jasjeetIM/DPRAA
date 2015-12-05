// project/DPRRA.cpp
// Dynamic Priority-based Round Robin Algorithm
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include "DPRRA.hpp"


/*
 * This is the constructor for a DPRRA object which contains a DCLL.
 * finish the job.
 *    Complexity: O(1)
 *         Input: none
 *        Output: none
 */
DPRRA::DPRRA() {
   process_list = new DCLL;
}

/*
 * This is the destructor for DPRRA which deletes the DCLL upon being called.
 *    Complexity: O(1)
 *         Input: none
 *        Output: none
 */
DPRRA::~DPRRA() {
   delete process_list;
}

/*
 *  This function returns a pointer to the DCLL.
 *         Complexity: O(1)
 *         Input: none
 *        Output: process list
 */
DCLL * DPRRA::getList() {
   return process_list;
}

/* This function uses merges sorted arrays.
 * 	Complexity: O(n)
 * 	Input: Two int arrays to be merged
 * 	Output: none
 */
void DPRRA:: merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

/*   This function sorts an array of times using mergesort.
 *   	Complexity: O(nlogn)
 *   	Input: Array to be sorted
 *   	Output: None
 */
void DPRRA::mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}


/*
 * This static function is executed in a new thread. It then calls the
 * process_adder_thread() function which enables multithreading.
 *    Complexity: O(1)
 *         Input: param
 *        Output: pointer to the thread
 */
void * DPRRA::process_adder(void * param) {
   DPRRA *non_static_object = (DPRRA *)param;
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
void * DPRRA::CPU_scheduler(void * param) {
   DPRRA *non_static_object = (DPRRA *)param;
   non_static_object->CPU_scheduler_thread();
   pthread_exit(0);
}


/*
 * This is a member function that adds new DCLLNodes to the DCLL. Each node
 * contains a process from the process array that is passed to the
 * simulate_DPRRA() function.
 *    Complexity: O(n)
 *         Input: none
 *        Output: pointer to the thread
 */
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
 * the DPRRA algorithm. It calculates time_quanta for every node and then
 * processes that node. Once the node has been processed (job has been
 * completed), it then removes that node from the DCLL and marks the completion
 * time in the job (Process).
 *    Complexity: O(1)
 *         Input: none
 *        Output: pointer to the thread
 */
void * DPRRA::CPU_scheduler_thread(void) {
   DCLLNode *temp;
   DCLLNode *CPU = 0;
   bool started = false;
   unsigned int completed_jobs, list_size, num_jobs;
   int total_time, waiting_time;
   float time_quanta, time_remaining;
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
         // total waiting time for all processes in the list
         total_time = process_list->getTotalTime();
         waiting_time = CPU->getData()->get_waiting_time();
         time_quanta = (Min_tq + (waiting_time/total_time)*(Max_tq - Min_tq));
         if (time_quanta > Max_tq) {
            time_quanta = Max_tq;
         }

        // pthread_mutex_lock(&print);
      //   cout << "Current time quanta is : " << time_quanta << endl;
        // pthread_mutex_unlock(&print);

         time_remaining = CPU->getData()->get_time_remaining() - time_quanta;
         CPU->getData()->set_time_remaining(time_remaining);
         while (CPU->getNext() == NULL) {
            pthread_cond_wait(&schC, &lock);
         }

         CPU->getData()->update_cs_count();

         temp = CPU->getNext();
         if (time_remaining <= 0.00) {
            completion_time = chrono::system_clock::now();
            CPU->getData()->set_completion_time(completion_time);
            ++completed_jobs;

           // pthread_mutex_lock(&print);
          //  cout << "JOB ID# " <<  CPU->getData()->get_id() << " has been completed." << endl;
           // pthread_mutex_unlock(&print);

	    process_list->removeNode(CPU);
            CPU = temp;

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
void DPRRA::simulate_DPRRA(vector<Process> &process_array) {
   int adder_creation, scheduler_creation;
   mrgArr = new int[process_array.size()];
   int q1, q2, q3;

  for (unsigned int i = 0; i< process_array.size(); ++i) {
	mrgArr[i] = process_array[i].get_time_required();
 }

   mergeSort(mrgArr, 0, process_array.size());

   q2 = (process_array.size() - 1)/2;
   q1 = q2/2;
   q3 = q2 + q2/2;


   Min_tq  = mrgArr[q1];
   Max_tq  = mrgArr[q3];

   cout << "Min " << Min_tq << ", Max " << Max_tq << endl;
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
