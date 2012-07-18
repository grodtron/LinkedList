#include "LinkedList.h"

template <typename T>
template <typename Comparator>
void LinkedList<T>::sort(){
   // sort the list in place, updating head->next and tail
   _mergesort<Comparator>(head->next, &(head->next), &tail);
}

template <typename T>
template <typename Comparator>
void LinkedList<T>::_mergesort(node * list, node ** ret_head, node ** ret_tail){
   const size_t MSORT_LENGTH_THRESHOLD = 1 << 3;

   node * fast;
   node * slow;
   size_t counter;

   Comparator sortsBefore;

   // -------------------- split ---------------------------- //

   for(
         fast = slow = list, counter = 0;
         fast->next && fast->next->next;
         slow = slow->next, fast = fast->next->next, ++counter
      );
   // TODO - is there any optimizations we could do during this pass?
   //        would it be worth it to check fast->value agaisnt slow->value and swap
   //        if they're out of order?
   //
   //        Would this actually help that much?

   // --------------------- sort ---------------------------- //

   // At this point, "slow" points to the middle of the list, "fast" points
   // to the last or second last element, and "counter" holds the length of
   // the two sublists

   if (counter <= MSORT_LENGTH_THRESHOLD){
      // if the sublists are less than a certain length threshold, then we
      // just pass the whole list through insertion sort instead of recursing
      // down all the way. This is the base case of the recursion
      _insertionsort<Comparator>(list, ret_head, ret_tail);
      return;
   }else{

      // otherwise we recursively sort both of the half lists and then merge them

      node * left;
      node * left_tail;
      node * right;
      node * right_tail;

      _mergesort<Comparator>(slow->next, &left, &left_tail);
      slow->next = NULL;
      _mergesort<Comparator>(list, &right, &right_tail);

   // -------------------- merge ---------------------------- //

      // At this point in the algorithm, left and right are both sorted

      // a couple quick checks that allow us to skip a merge if we're lucky (very lucky)
      // if everything in one list is less than everything in the other, then
      // we can just concatenate them
      //
      // This should give a good best case for nearly sorted input
      // although my insertion sort has its best case for reverse sorted input...
      // so maybe that's a bit counter-productive...
      //
      // TODO - do some testing with sorted and reverse sorted inputs, see what we end up with.
      //        hopefully insertion sorts worst case doesn't just defeat this one's best case
      if( sortsBefore(left_tail->value, right->value) ){
         left_tail->next = right;
         *ret_head = left;
         *ret_tail = right_tail;
         return;
      }
      if( sortsBefore(right_tail->value, left->value) ){
         right_tail->next = left;
         *ret_head = right;
         *ret_tail = left_tail;
         return;
      }

      // ------------ actual merge ----------- //

      // the output list
      node * out;

      // we need to start the loop with a node, so we grab it
      // from the start of one of the lists.
      if(sortsBefore(left->value, right->value)){
         out = left;
         left = left->next;
      }else{
         out = right;
         right = right->next;
      }

      // we don't keep track of the head inside the merging procedure, so we set
      // the output head here (it won't change in the loop)
      *ret_head = out;

      // we merge until we've used up one of the lists
      while(left && right){

         if(sortsBefore(left->value, right->value)){
            out->next = left;
            out = left;
            left = left->next;
         }else{
            out->next = right;
            out = right;
            right = right->next;
         }
      }

      // At this point, either left or right is empty, out is the tail of the sorted
      // output list, and either right or left has one or more elements in it which are
      // in sorted order and greater than every element in the output list
      //
      // We are guaranteed that one list is non-empty because we only take one element from one
      // of the lists on each iteration, and we only iterate if each list has atleast one
      // element

      // we simply concatenate the end of the list that we didn't use up onto the output.
      if(left){
         out->next = left;
         *ret_tail = left_tail;
      }else{
         out->next = right;
         *ret_tail = right_tail;
      }
   }
}

template <typename T>
void LinkedList<T>::_quicksort(node * list, node ** ret_head, node ** ret_tail){

   // insertion sort will take care of lists shorter than this threshold
   // Extremely non-rigorous and unscientific testing has shown that this
   // value works. Shaves off around 1 second (5%) when sorting ~16,000,000 integers
   const size_t QSORT_LENGTH_THRESHOLD = 1 << 4;

   node * lower        = NULL;
   node * lower_tail   = NULL;
   size_t lower_len    = 0;
   node * greater      = NULL;
   node * greater_tail = NULL;
   size_t greater_len  = 0;
   node * equal        = NULL;
   node * equal_tail   = NULL;

   node * temp;

   const T & pivot = list->value;

   // ------------------- partition --------------------------- //

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
         ++lower_len;
      }else{
         if (!greater) greater_tail = temp;
         temp->next = greater;
         greater = temp;
         ++greater_len;
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

   // -------------------- recurse -------------------------- //

   if (lower && lower->next){
      // there is 2 or more elements in lower, so it must be sorted
      if (lower_len > QSORT_LENGTH_THRESHOLD){
         _quicksort(lower, &lower, &lower_tail);
      }else{
         _insertionsort(lower, &lower, &lower_tail);
      }
   }else{
      // there is 0 or 1 elements in lower, so either its head is its tail,
      // or its head is NULL and it's tail should be NULLed
      lower_tail = lower;
   }

   // same as above
   if (greater && greater->next){
      if (greater_len > QSORT_LENGTH_THRESHOLD){
         _quicksort(greater, &greater, &greater_tail);
      }else{
         _insertionsort(greater, &greater, &greater_tail);
      }
   }else{
      greater_tail = greater;
   }

   // At this point in the algorithm we have 3 sorted lists. All elements in lower sort
   // lower than all elements in equal, and all elements in equal sort lower than all
   // elements in greater. To form one sorted list, we just have to concatenate these 3
   // properly

   // --------------------- recombine ------------------------ //

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

template <typename T>
template <typename Comparator>
void LinkedList<T>::_insertionsort(node * list, node ** ret_head, node ** ret_tail){
   // basic idea is to take elements from unsorted list and place them into sorted list
   // one by one in the correct position

   // After each pass the unsorted list is smaller by one and the sorted list is larger by one

   // one little oddity is that this will have an inverted best and worst case.
   // E.g. a reverse sorted input is the best case, and a sorted input is the worst case...

   Comparator sortsBefore;

   node * temp;

   node * head;
   node * tail;

   node * curr;
   node * prev;

   // we want to start off with a non-empty sorted list,
   // because it is more convenient
   head = tail = list;

   // move the list so that it's pointing to the next element
   list = list->next;

   // we have to make sure we break it off from its parent list,
   // otherwise all we've done is grabbed a pointer to the other list
   // N.B. this must be done AFTER the line above, otherwise we turn
   // our list into a list of 1 element.
   head->next = NULL;

   while(list){

      // pop the next thing off the unsorted list
      temp = list;
      list = list->next;

      // set up our output temp variables
      prev = NULL;
      curr = head;

      while(curr){

         if(sortsBefore(temp->value, curr->value)){
            // in this case, we know where to insert
            break;
         }else{
            // move along the sorted list
            prev = curr;
            curr = curr->next;
         }
      }

      // either we've found a spot in the list, or we've traversed
      // the entire list. In either case we now know where to insert
      // our new element

      temp->next = curr;

      // track the position of the tail
      if (!curr) tail = temp;

      // also track the position of the head
      if (prev){
         prev->next = temp;
      }else{
         head = temp;
      }
   }

   // set our output params
   *ret_head = head;
   *ret_tail = tail;
}
