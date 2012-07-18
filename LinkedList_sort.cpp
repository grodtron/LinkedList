#include "LinkedList.h"

template <typename T>
void LinkedList<T>::sort(){
   // sort the list in place, updating head->next and tail
   _quicksort(head->next, &(head->next), &tail);

}

template <typename T>
void LinkedList<T>::_quicksort(node * list, node ** ret_head, node ** ret_tail){

   node * lower        = NULL;
   node * lower_tail   = NULL;
   node * greater      = NULL;
   node * greater_tail = NULL;
   node * equal        = NULL;
   node * equal_tail   = NULL;

   node * temp;

   const T & pivot = list->value;

   // partition
   while(list){

      temp = list;
      list = list->next;

      // TODO - use some kind of comparator function ([-1,0,1]) and a switch statement

      if(temp->value == pivot){
         // The structure of each of these cases is the same, so I'm only
         // exlaining it once.

         // if the list is NULL when we get here, then the thing we're adding
         // becomes both the head and the tail
         if (!equal) equal_tail = temp;

         // this always happens, and is just pushing a new node to the list
         temp->next = equal;

         // update the head of the list
         equal = temp;
      }else if(temp->value < pivot){
         if (!lower) lower_tail = temp;
         temp->next = lower;
         lower = temp;
      }else{
         if (!greater) greater_tail = temp;
         temp->next = greater;
         greater = temp;
      }
   }

   // At this point in the algorithm, the original list is empty and we have three new lists
   //    lower   - a list of all elements that sort lower than the pivot. This list may be empty
   //              this list is not sorted
   //
   //    greater - a list of all the elements that sort greater than the pivot. This list may be empty
   //              this list is not sorted
   //
   //    equal   - a list of all the elements that sort equal to the pivot. This list is guaranteed to
   //              have at least one element (the pivot itself).
   //              This list IS sorted (all the elements are "equal" to each other in terms of sort order)

   // recurse

   if (lower && lower->next){
      // there is 2 or more elements in lower, so it must be sorted
      _quicksort(lower, &lower, &lower_tail);
   }else{
      // there is 0 or 1 elements in lower, so either its head is its tail,
      // or its head is NULL and it's tail should be NULLed
      lower_tail = lower;
   }

   // same as above
   if (greater && greater->next){
      _quicksort(greater, &greater, &greater_tail);
   }else{
      greater_tail = greater;
   }

   // At this point in the algorithm we have 3 sorted lists. All elements in lower sort
   // lower than all elements in equal, and all elements in equal sort lower than all
   // elements in greater. To form one sorted list, we just have to concatenate these 3
   // properly

   // recombine

   // We start with the lower list. If it exists, then the output just
   // becomes equal to it. Otherwise, it is set to NULL, which is what we would want anyway
   *ret_head = lower;
   *ret_tail = lower_tail;

   // we are guaranteed that "equal" will always have at least one
   // element, because we took its value from the list. The other two
   // could conceivably be empty though.
   if(*ret_tail){
      // If lower was non-empty, then we concatenate equal to it
      (*ret_tail)->next = equal;
      *ret_tail = equal_tail;
   }else{
      // otherwise the output is set to equal
      *ret_head = equal;
      *ret_tail = equal_tail;
   }

   // We do want to check to make sure that greater is not NULL, otherwise
   // we will accidentally NULL ret_tail, which we do not want.
   if(greater){
      (*ret_tail)->next = greater;
      *ret_tail = greater_tail;
   }

   // At this point ret_tail and ret_head point to the head and tail of the sorted input list
}
