#include <iostream>
using std::cout;
using std::endl;

#include "LinkedList.h"

#include <ctime>
// time()
#include <cstdlib>
// srand(), rand()

int main()
{

   srand(time(0));

   const int length = 1<<22;

   LinkedList<int> list(length);

   for(int i = 0; i < length; ++i){
      list.addFirst( rand() % (length << 1) );
   }

   cout << "sorting... ";
   cout.flush();

   list.sort();

   cout << "done" << endl;

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
