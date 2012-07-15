#include <iostream>
using std::cout;
using std::endl;

#include "LinkedList.h"

int main()
{

   const int length = 2<<20;

   LinkedList<int> list(8);

   int i;

   for(i = 0; i < length; ++i){
      list.addFirst(i);
      list.addLast(i);
   }

   LinkedList<int>::iterator it = list.begin();
   LinkedList<int>::iterator end= list.end();
   
   return 0;
}
