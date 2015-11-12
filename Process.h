#ifndef PROCESS_H
#define PROCESS_H

using namespace std;

class Process
{
private:
    double arrival_time, completion_time, latest_time_quantum, CPU_time_remaining;
    int total_CPU_time_required;

public:
    Process(int time_required); // constructor that creates job based on total CPU time required to finish the job
    int get_CPU_time_required(); // get total CPU time required to finish the job
    void set_CPU_time_required(int time); // set total CPU time required to finish the job
    double get_arrival_time();  // get clock time that the process arrived at the CPU/system
    void set_arrival_time(double time); // set clock time that the process arrived  at the CPU/system
    double get_completetion_time(); // get clock time that the process was completed
    void set_completion_time(double time); // set clock time that the process was completed
    double get_latest_time_quantum(); // set the time_quantum that the process will be executed for in the CPU - calculated before CPU entry
    void set_latest_time_quantum(double tme); // get the time_quantum that the process will be executed for in the CPU - calculated before CPU entry
    double get_CPU_time_remaining(); // get the amount of time remaining to complete this process
    void set_CPU_time_remaining(double time); // set the amount of time remaining to complete this process
};


#endif // PROCESS_H_INCLUDED
