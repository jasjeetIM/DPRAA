#include "Process.h"
#include <chrono>
#include <iostream> 
using namespace std; 

Process::Process(long int time_required){

    total_CPU_time_required = time_required; 
    latest_time_quantum = 0.0;
    CPU_time_remaining = 0.0;

}

long int Process::get_CPU_time_required(){
   return total_CPU_time_required;
}

void Process::set_CPU_time_required(long int time){
    total_CPU_time_required = time;
}

chrono::system_clock::time_point Process::get_arrival_time(){
    return arrival_time;
}

void Process::set_arrival_time(chrono::system_clock::time_point time){
    arrival_time = time;
}

system_clock::time_point Process::get_completetion_time(){
    return completion_time;
}

void Process::set_completion_time(chrono::system_clock::time_point time){
    completion_time = time;
}
long int Process::get_latest_time_quantum(){
    return latest_time_quantum;
}

void Process::set_latest_time_quantum(long int time){
    latest_time_quantum= time;
}

long int Process::get_CPU_time_remaining(){
    return CPU_time_remaining;
}

void Process::set_CPU_time_remaining(long int time){
    CPU_time_remaining = time;
}

long int Process::getWaitingTime()
{
   
 chrono::system_clock::time_point a = chrono::system_clock::now();  
  waiting_time = a.time_since_epoch().count()  -  arrival_time.time_since_epoch().count();  
	return waiting_time; 
}


