#include "LinkedList.h"

template <typename T>
void LinkedList<T>::sort(){

}

template <typename T>
void LinkedList<T>::_quicksort(node * list, node ** ret_head, node ** ret_tail){

   node * lower = NULL;
   node * greater = NULL;
   node * equal = NULL;

   node * temp;

   T & pivot = list->value;

   // partition
   while(list){

      temp = list;
      list = list->next;

      if(temp->value == pivot){
         temp->next = equal;
         equal = temp;
      }else if(temp->value < pivot){
         temp->next = lower;
         lower = temp;
      }else{
         temp->next = greater;
         greater = temp;
      }

   }

   // recurse
   if (lower && lower->next){
      _quicksort(lower, &lower, &lower_tail);
   }else{
      lower_tail = lower;
   }

   if (greater && greater->next){
      _quicksort(greater, &greater, &greater_tail);
   }else{
      greater_tail = greater;
   }

   // recombine
   
   // We start with the lower list. If it exists, then the output just
   // becomes equal to it. Otherwise, it is set to NULL, which is what we would want
   *ret_head = lower;
   *ret_tail = lower_tail;

   // we are guaranteed that "equal" will always have at least one
   // element, because we took it's value from the list. The other two
   // could conceivably be empty though.
   if(*ret_tail){
      (*ret_tail)->next = equal;
      *ret_tail = equal_tail;
   }else{
      *ret_head = lower;
      *ret_tail = lower_tail;
   }

   // We do want to check to make sure that greater is not NULL, otherwise
   // we will accidentally NULL ret_tail, which we do not want.
   if(greater){
      (*ret_tail)->next = greater;
      *ret_tail = greater_tail;
   }
}
