// project/Process.cpp
// Process
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#include "Process.hpp"

/*
 * This is the constructor that creates job based on total CPU time required to
 * finish the job.
 *    Complexity: O(1)
 *         Input: time required
 *        Output: none
 */
Process::Process(long int t) {
   time_required = t;
   latest_tq = 0.0;
   time_remaining = 0.0;
}

/*
 * This function get the total CPU time required to finish the job.
 *    Complexity: O(1)
 *         Input: none
 *        Output: time required
 */
long int Process::get_time_required() {
   return time_required;
}

/*
 * This function set the total CPU time required to finish the job.
 *    Complexity: O(1)
 *         Input: time required
 *        Output: none
 */
void Process::set_time_required(long int t) {
   time_required = t;
}

/*
 * This function get the clock time that the process arrived at CPU/system.
 *    Complexity: O(1)
 *         Input: none
 *        Output: arrival time
 */
system_clock::time_point Process::get_arrival_time() {
   return arrival_time;
}

/*
 * This function get the clock time that the process arrived at CPU/system.
 *    Complexity: O(1)
 *         Input: arrival time
 *        Output: none
 */
void Process::set_arrival_time(system_clock::time_point t) {
   arrival_time = t;
}

/*
 * This function get the clock time that the process was completed.
 *    Complexity: O(1)
 *         Input: none
 *        Output: completion time
 */
system_clock::time_point Process::get_completetion_time() {
   return completion_time;
}

/*
 * This function set the clock time that the process was completed.
 *    Complexity: O(1)
 *         Input: completion time
 *        Output: none
 */
void Process::set_completion_time(system_clock::time_point t) {
   completion_time = t;
}

/*
 * This function get the time_quantum that the process will be executed for in
 * the CPU, calculated before CPU entry.
 *    Complexity: O(1)
 *         Input: none
 *        Output: lastest time quantum
 */
long int Process::get_latest_tq() {
   return latest_tq;
}

/*
 * This function set the time_quantum that the process will be executed for in
 * the CPU, calculated before CPU entry.
 *    Complexity: O(1)
 *         Input: lastest time quantum
 *        Output: none
 */
void Process::set_latest_tq(long int t) {
   latest_tq = t;
}

/*
 * This function get the amount of time remaining to complete this process.
 *    Complexity: O(1)
 *         Input: none
 *        Output: time remaining
 */
long int Process::get_time_remaining() {
   return time_remaining;
}

/*
 * This function set the amount of time remaining to complete this process.
 *    Complexity: O(1)
 *         Input: time remaining
 *        Output: none
 */
void Process::set_time_remaining(long int t) {
   time_remaining = t;
}

/*
 * This function calculates the waiting time of the process.
 *    Complexity: O(1)
 *         Input: none
 *        Output: waiting time
 */
long int Process::get_waiting_time() {
   system_clock::time_point tp = system_clock::now();
   waiting_time = tp.time_since_epoch().count() - arrival_time.time_since_epoch().count();
   return waiting_time;
}
