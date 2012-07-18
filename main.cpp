#include <iostream>
using std::cout;
using std::endl;

#include "LinkedList.h"

#include "timer.h"

#include <ctime>
// time()
#include <cstdlib>
// srand(), rand()

int main()
{

   srand(time(0));

   const int length = 1<<20;

   timer tim;

   LinkedList<int> list(length);

   cout << "constructing list of " << length << " random integers... ";
   cout.flush();
   for(int i = 0; i < length; ++i){
      list.addFirst( rand() % (length << 1) );
   }
   cout << "done" << endl;

   cout << "sorting... ";
   cout.flush();

   tim.start();
   list.sort();
   tim.end();

   cout << "done" << endl;
   cout << "took " << (tim.duration() * 1e-6) << " seconds" << endl;
   // ^ have to convert from microseconds

   LinkedList<int>::iterator it = list.begin();
   LinkedList<int>::iterator end= list.end();

   bool sorted = true;

   int prev = *it;
   ++it;

   cout << "Verifying sortedness of list... ";
   cout.flush();
   for( ; sorted && (it != end); ++it){
      sorted = sorted && (prev <= *it);
      prev = *it;
   }
   cout << "done" << endl;

   if(sorted){
      cout << "SUCCESS! List is sorted" << endl;
   }else{
      cout << "FAILURE! List ain't sorted" << endl;
   }
   
   return 0;
}
