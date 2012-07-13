#include <iostream>
using std::cout;
using std::endl;

#include "LinkedList.h"

int main()
{

   const int length = 16;

   LinkedList<int> list(length);

   int i;

   for(i = 0; i < (length/2); ++i){
      list.addFirst(i);
   }

   for(     ; i < length; ++i){
      list.addLast(i);
   }

   LinkedList<int>::iterator it = list.begin();
   LinkedList<int>::iterator end= list.end();

   it = list.begin();

   for(i = 0; i < 4; ++i) ++it;

   list.remove(it);
   list.remove(it);

   it = list.begin();

   list.addBefore(42, it);

   list.addAfter(256, it);

   for(it = list.begin(); it != end; ++it){
      cout << *it << endl;
   }
   
   return 0;
}
