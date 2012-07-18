/*
 *  A class that provides a simple timer
 *  Works in Windows and Linux, resolution is hardware dependant
 *
 *
 *  Copyleft Gordon Bailey 2012 - All wrongs reserved
 *
 * */

#include "timer.h"

#ifdef _WIN32

#include <cstdlib>

#include <iostream>
using std::endl;
using std::cerr;

timer::timer() : ready(false) {
   bool success = QueryPerformanceFrequency(&counter_freq);
   if(!success){
      cerr << "Error, QueryPerformanceFrequency failed." << endl;
      system("pause");
      exit(EXIT_FAILURE);
   }
}

void timer::start() {
   ready = false;
   bool success = QueryPerformanceCounter(&start_time);
   if(!success){
      cerr << "Error, QueryPerformanceCounter failed." << endl;
      system("pause");
      exit(EXIT_FAILURE);
   }
}

void timer::end(){
   ready = true;
   bool success = QueryPerformanceCounter(&end_time);
   if(!success){
      cerr << "Error, QueryPerformanceCounter failed." << endl;
      system("pause");
      exit(EXIT_FAILURE);
   }
}

// there is probably some unnecessary typecasting here, but better safe than sorry
double timer::duration(){
   if (ready){
	   return 1e6 * (((double)(end_time.QuadPart - start_time.QuadPart)) / ((double)counter_freq.QuadPart));
   }else{
      return 0;
   }
}

#else

timer::timer() : ready(false) {}

void timer::start() {
   ready = false;
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
}

void timer::end(){
   clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
   ready = true;
}

double timer::duration(){
   if (ready){
      return 1e6 * (difftime(end_time.tv_sec, start_time.tv_sec) + (1e-9 * (double)(end_time.tv_nsec - start_time.tv_nsec)));
   }else{
      return 0;
   }
}

#endif
