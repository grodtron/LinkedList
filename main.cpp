#include <iostream>
using std::cout;
using std::endl;

#include <functional>
// std::less

#include "LinkedList.h"

#include "timer.h"

#include <ctime>
// time()
#include <cstdlib>
// srand(), rand()

int main()
{

   srand(time(0));

   const size_t length = 1<<24;

   timer tim;

   LinkedList<int> list(length);

   cout << "constructing list of " << length << " random integers... ";
   cout.flush();
   for(size_t i = 0; i < length; ++i){
      list.addFirst( rand() % (length << 1) );
   }
   cout << "done" << endl;

   cout << "sorting... ";
   cout.flush();

   tim.start();
   list.sort<std::less<int> >();
   tim.end();

   cout << "done" << endl;
   cout << "took " << (tim.duration() * 1e-6) << " seconds" << endl;
   // ^ have to convert from microseconds

   LinkedList<int>::iterator it = list.begin();
   LinkedList<int>::iterator end= list.end();

   bool sorted = true;

   size_t length_counter = 0;
   int prev = *it;
   ++it;
   ++length_counter;

   cout << "Verifying sortedness and length of list... ";
   cout.flush();
   for( ; sorted && (it != end); ++it){
      sorted = sorted && (prev <= *it);
      prev = *it;
      ++length_counter;
   }
   cout << "done" << endl;

   if(sorted){
      if(length_counter == length){
         cout << "SUCCESS! List is sorted and the correct length!" << endl;
      }else{
         cout << "FAILURE! List is sorted, but the wrong length! (Is " << length_counter << " long, should be " << length << ")" << endl;
      }
   }else{
      if(length_counter == length){
         cout << "FAILURE! List ain't sorted (but it is the right length)" << endl;
      }else{
         cout << "FAILURE! List ain't sorted, and it's not even the right length! (Is " << length_counter << " long, should be " << length << ")" << endl;
      }
   }

   #ifdef _WIN32
   system("pause");
   #endif
   
   return 0;
}
