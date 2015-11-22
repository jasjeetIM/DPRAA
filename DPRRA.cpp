#include "DPRRA.h"
#include "DCLL.h"
#include "Process.h"
#include <pthread.h>
#include <chrono>
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

#define MAX_TIME_QUANTA 5

DPRRA::DPRRA() {
    process_list = new DCLL;
}

DPRRA::~DPRRA(){
    delete process_list;

}


DCLL * DPRRA::getList(){
return process_list; 
}


void * DPRRA:: process_adder(void * param){
           DPRRA * non_static_object = (DPRRA *)(param); 
           non_static_object->process_adder_thread(); 
           pthread_exit(0); 
}

 void *DPRRA:: CPU_scheduler(void * param){
	DPRRA * non_static_object = (DPRRA *)(param); 
	non_static_object->CPU_scheduler_thread(); 
        pthread_exit(0); 
}

void *DPRRA:: process_adder_thread(void){
//cout << "adder is working on this list " << process_list << endl;
       // pthread_mutex_lock(&lock); 
	unsigned int size =  array_pointer->size(); 
//        pthread_mutex_unlock(&lock); 
	for (unsigned int i = 0; i<size; i++)
    	{
        	chrono::system_clock:: time_point now = chrono::system_clock::now();     
	// pthread_mutex_lock(&print);    
	//	cout << "adder thread is running " << endl; 
        //	pthread_mutex_unlock(&print); 
//		pthread_mutex_lock(&lock); 
       		 (*array_pointer)[i].set_arrival_time(now); 
		process_list->insertNode(&(*array_pointer)[i]);
 //      		cout << "added one job to list " << endl;
//		 pthread_mutex_unlock(&lock);
  

    }
  
//cout << process_list->getHead()->getPrevious() <<  " GOOOOO NUTES " << endl;

return 0; 
}

void * DPRRA::CPU_scheduler_thread(void){

 //	cout << "Scheculer is working on this list " << process_list << endl;   
        DCLLNode * CPU= 0; 
	while (!CPU)
	{
//		pthread_mutex_lock(&print); 
//		cout << "trying to get cpu "<<endl;
//		pthread_mutex_unlock(&print); 
//		pthread_mutex_lock(&lock); 
		CPU =process_list->getHead();
  //  		pthread_mutex_unlock(&lock); 
   	}
          
	DCLLNode * temp;
   	 bool started = false;
    	unsigned int number_of_jobs_completed, list_size, number_of_jobs;
    	number_of_jobs_completed = list_size = 0;  
   
//	pthread_mutex_lock(&lock); 
        number_of_jobs = array_pointer->size();
  //      pthread_mutex_unlock(&lock);  
	chrono::system_clock::duration time_quanta, process_waiting_time, total_time, process_time_remaining;

   	 while ( started == false) // Wait until the list has at least 1 process
    	{
      
//		pthread_mutex_lock(&lock);
        	list_size = process_list->getSize();
  //      	cout << list_size << endl;  
//		cout << "checked for 1 unit size" << endl;
  //     		pthread_mutex_unlock(&lock);  
		if (list_size > 0) // If it has 1 process, enter and set started to true to exit the outer most while loop
        	{
            		started = true;

            		while (number_of_jobs_completed != number_of_jobs )  // keep cycling through the list until all jobs have been completed
            		{
//				pthread_mutex_lock(&lock); 
 				list_size=process_list->getSize(); 
  //              		pthread_mutex_unlock(&lock); 
                		if (list_size  > 0) // processing of one job at a time
                		{
//		    	              pthread_mutex_lock(&lock)	
		 			total_time = process_list->getTotalTime(); // total waiting time for all the processes in the list
          		 	
					process_waiting_time = CPU->getData()->getWaitingTime(
						cout << process_waiting_time  << endl;
                    		      	time_quanta = ((process_waiting_time)/total_time)*MAX_TIME_QUANTA; // quanta = (process waiting time)/(total waiting time)*(max time quanta)

                    			process_time_remaining = (CPU->getData()->get_CPU_time_remaining())- time_quanta;
                    			CPU->getData()->set_CPU_time_remaining(process_time_remaining); // update process's time remaining
//					cout << "four "<<endl;
                    			temp = CPU->getNext();
  //                                      cout << "This is the CPU " << CPU << endl;

                    			if (process_time_remaining <= 0)
                    			{	cout << process_list->getHead()->getPrevious() << endl;
						process_list->removeNode(process_list->getHead());
			
                        			number_of_jobs_completed++;
                                          
                        			CPU = temp;
                        			cout <<  number_of_jobs_completed << " jobs have been completed " << endl;
                    			}
                    			else
                    			{
                        			CPU = CPU->getNext();
                    			}
//					pthread_mutex_unlock(&lock); 
                		}
            		}
          		cout << "ALL JOBS HAVE BEEN COMPLTED." << endl;

       		 }	

    }
  return 0; 
}


void DPRRA::simulate_DPRRA(vector <Process> &process_array){
   
    pthread_mutex_init(&lock, 0); 
    int adder_creation, scheduler_creation;
    array_pointer = &process_array;
   pthread_mutex_init(&print, 0); 
    
    adder_creation = pthread_create(&adder,0,&process_adder, this );
      if (adder_creation){
            cout << "Error:unable to create thread," << adder_creation  << endl;
            exit(-1);
      }

    scheduler_creation = pthread_create(&scheduler,0,&CPU_scheduler, this);
      if (scheduler_creation){
            cout << "Error:unable to create thread," << scheduler_creation << endl;
            exit(-1);
      }
cout << "threads have been joined " << endl;	
      pthread_join(adder,0);
      pthread_join(scheduler, 0);
      cout << "threads have been joined" << endl;
	pthread_mutex_destroy(&lock); 
      //THE ALGORITHM HAS BEEN COMPLETED

}
