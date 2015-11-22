#include "Process.h"
#include <chrono>
#include <iostream> 
using namespace std::chrono::system_clock; 

Process::Process(duration time_required){

    total_CPU_time_required = time_required;
    arrival_time = 0.0;
    completion_time = 0.0;
    latest_time_quantum = 0.0;
    CPU_time_remaining = 0.0;

}

duration Process::get_CPU_time_required(){
   return total_CPU_time_required;
}

void Process::set_CPU_time_required(duration time){
    total_CPU_time_required = time;
}

time_point Process::get_arrival_time(){
    return arrival_time;
}

void Process::set_arrival_time(time_point time){
    arrival_time = time;
}

time_point Process::get_completetion_time(){
    return completion_time;
}

void Process::set_completion_time(time_point time){
    completion_time = time;
}
duration Process::get_latest_time_quantum(){
    return latest_time_quantum;
}

void Process::set_latest_time_quantum(duration time){
    latest_time_quantum= time;
}

duration Process::get_CPU_time_remaining(){
    return CPU_time_remaining;
}

void Process::set_CPU_time_remaining(duration time){
    CPU_time_remaining = time;
}

duration Process::getWaitingTime()
{
    waiting_time = now() -  arrival_time.time_since_epoch();  
	return waiting_time; 
}


