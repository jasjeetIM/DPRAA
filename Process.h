#ifndef PROCESS_H
#define PROCESS_H

#include <chrono>

using namespace std::chrono::system_clock; 

class Process
{
private:
    time_point  arrival_time, completion_time; 
    duration CPU_time_required, CPU_time_remaining, waiting_time; 

public:
    Process(duration time_required); // constructor that creates job based on total CPU time required to finish the job
    duration get_CPU_time_required(); // get total CPU time required to finish the job
    void set_CPU_time_required(duration time); // set total CPU time required to finish the job
    time_point get_arrival_time();  // get clock time that the process arrived at the CPU/system
    void set_arrival_time(time_point time); // set clock time that the process arrived  at the CPU/system
    time_point get_completetion_time(); // get clock time that the process was completed
    void set_completion_time(time_point time); // set clock time that the process was completed
    duration get_latest_time_quantum(); // set the time_quantum that the process will be executed for in the CPU - calculated before CPU entry
    void set_latest_time_quantum(duration time); // get the time_quantum that the process will be executed for in the CPU - calculated before CPU entry
    duration get_CPU_time_remaining(); // get the amount of time remaining to complete this process
    void set_CPU_time_remaining(duration time); // set the amount of time remaining to complete this process
    duration getWaitingTime(); // return waiting time for process	
   
};


#endif // PROCESS_H_INCLUDED
