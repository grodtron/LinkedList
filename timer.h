#ifndef TIMER_H
#define TIMER_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <time.h>
#endif

class timer{

#ifdef _WIN32
      LARGE_INTEGER start_time;
      LARGE_INTEGER end_time;
      LARGE_INTEGER counter_freq;
#else
      struct timespec start_time;
      struct timespec end_time;
#endif

      bool ready;
   public:
      void start();
      void end();
      double duration();
      timer();
};

#endif
