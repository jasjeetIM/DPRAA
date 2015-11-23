// project/Process.hpp
// Process
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <chrono>
#include <iostream>

using namespace std::chrono;

class Process {
private:
   system_clock::time_point arrival_time;
   system_clock::time_point completion_time;
   long int total_CPU_time_required, CPU_time_remaining, waiting_time, latest_time_quantum;

public:
   Process(long int time_required); // constructor that creates job based on total CPU time required to finish the job
   long int get_CPU_time_required(); // get total CPU time required to finish the job
   void set_CPU_time_required(long int time); // set total CPU time required to finish the job
   system_clock::time_point get_arrival_time();  // get clock time that the process arrived at the CPU/system
   void set_arrival_time(system_clock::time_point time); // set clock time that the process arrived  at the CPU/system
   system_clock::time_point get_completetion_time(); // get clock time that the process was completed
   void set_completion_time(system_clock::time_point time); // set clock time that the process was completed
   long int  get_latest_time_quantum(); // set the time_quantum that the process will be executed for in the CPU - calculated before CPU entry
   void set_latest_time_quantum(long int time); // get the time_quantum that the process will be executed for in the CPU - calculated before CPU entry
   long int get_CPU_time_remaining(); // get the amount of time remaining to complete this process
   void set_CPU_time_remaining(long int time); // set the amount of time remaining to complete this process
   long int getWaitingTime(); // return waiting time for process
};

#endif // PROCESS_HPP
