#include "Process.h"

using namespace std;

Process::Process(int time_required){

    total_CPU_time_required = time_required;
    arrival_time = 0.0;
    completion_time = 0.0;
    latest_time_quantum = 0.0;
    CPU_time_remaining = 0.0;

}

int Process::get_CPU_time_required(){
   return total_CPU_time_required;
}

void Process::set_CPU_time_required(int time){
    total_CPU_time_required = time;
}

double Process::get_arrival_time(){
    return arrival_time;
}

void Process::set_arrival_time(double time){
    arrival_time = time;
}

double Process::get_completetion_time(){
    return completion_time;
}

void Process::set_completion_time(double time){
    completion_time = time;
}

double Process::get_latest_time_quantum(){
    return latest_time_quantum;
}

void Process::set_latest_time_quantum(double time){
    latest_time_quantum= time;
}

double Process::get_CPU_time_remaining(){
    return CPU_time_remaining;
}

void Process::set_CPU_time_remaining(double time){
    CPU_time_remaining = time;
}
