// project/Process.hpp
// Process
// ----------------------------------------------
// Authors:  Jasjeet Dhaliwal, Sui Fung Alex Wong
// Date:     11/23/2015

#ifndef PROCESS_HPP
#define PROCESS_HPP

// include libraries

#include <chrono>
#include <iostream>

using namespace std::chrono;

class Process {
   private:
      // variables
      system_clock::time_point arrival_time;
      system_clock::time_point completion_time;
      int time_required, waiting_time;
      float time_remaining, latest_tq;
      unsigned int cs_count;
      int identity;
   public:
      // function declarations
      Process(int time_required, int id);
      ~Process() {}

      void reset_data();

      // time required
      int get_time_required();
      void set_time_required(int t);

      // arrival time
      system_clock::time_point get_arrival_time();
      void set_arrival_time(system_clock::time_point t);

      // completion time
      system_clock::time_point get_completion_time();
      void set_completion_time(system_clock::time_point time);

      // latest time quantum
      float get_latest_tq();
      void set_latest_tq(float time);

      // time remaining
      float get_time_remaining();
      void set_time_remaining(float time);

      // waiting time
      int get_waiting_time();

      // context switch count
      unsigned int get_cs_count();
      void update_cs_count();

	int get_id();

};

#endif // PROCESS_HPP
