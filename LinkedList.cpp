#include "LinkedList.h"

// construct a list of a given size
template <typename T>
LinkedList<T>::LinkedList(int size)

   :
   head(new LinkedList<T>::node),
   tail(head),

   _length(0),

   allocatedBlocks(NULL),
   freedNodes(NULL),

   lastMemblockSize(size),

   currentAllocatedBlock(new LinkedList<T>::node[size]),
   nextFreeNode(currentAllocatedBlock + size - 1)

{
   head->next = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
   if (freedNodes) delete freedNodes;
   if (allocatedBlocks){

      // iterating is better than popping off, because popping
      // actually forces the creation of a new list to track the
      // popped nodes
      //
      // Creating a new list is obviously a bit counterproductive
      // when we're trying to destruct...

      LinkedList<void *>::iterator it  = allocatedBlocks->begin();
      LinkedList<void *>::iterator end = allocatedBlocks->end();

      while(it != end){
         delete[] (LinkedList<T>::node *) *it;
         ++it;
      }

      delete allocatedBlocks;
   }
   // TODO - valgrind reports weird problems with the line below.
   // I don't see why there would be any and it runs perfectly fine.
   // should make a stackoverflow question about this later.
   delete currentAllocatedBlock; // <-- this line
   delete head;
}

template<typename T>
struct LinkedList<T>::node * LinkedList<T>::getNode(){

   struct LinkedList<T>::node * newNode;

   // first check in our list of random freed nodes, we want
   // to consume them first before going to the nice supply
   //
   // this is like recycling, the other one is like extracting
   // new resources.
   if(freedNodes && !freedNodes->empty()){

      newNode = (struct LinkedList<T>::node *) freedNodes->popFirst();
      // TODO - delete the whole list if it is empty. Is this a good idea?
      // I don't really know...

   // then if not, take it from our current block
   }else{
      // This means we need to allocate a new check of nodes.
      // TODO - deal with expo-increasing block sizes
      // TODO - deal with failed allocations (reduce size and retry)
      if(nextFreeNode < currentAllocatedBlock){

         if (!allocatedBlocks){
            allocatedBlocks = new LinkedList<void *>;
         }
         allocatedBlocks->addFirst((void *) currentAllocatedBlock);

         // keep doubling the size each time until it overflows
         lastMemblockSize  = (lastMemblockSize * 2) < lastMemblockSize ? lastMemblockSize : lastMemblockSize * 2;

         // try to allocate a new block, halving the size if it fails, and keeping on trying
         bool successfullyAllocated = false;
         while(!successfullyAllocated && lastMemblockSize > 1){
            successfullyAllocated = true;
            try{
               currentAllocatedBlock = new struct LinkedList<T>::node[lastMemblockSize];
            }catch(std::bad_alloc & ){
               lastMemblockSize /= 2;
               successfullyAllocated = false;
               // if we are not able to allocate anything, then let the exception bubble up
               if (lastMemblockSize == 0) throw;
            }
         }

         nextFreeNode = currentAllocatedBlock + lastMemblockSize - 1;
      }

      newNode = nextFreeNode;
      --nextFreeNode;
   }

   return newNode;
}

template<typename T>
void LinkedList<T>::freeNode(struct LinkedList<T>::node * oldNode){

   // TODO - figure out a good default size for this in relation to the size
   // of the rest of the list.
   //
   // I guess it is kind of arbitrary/based on guesses/heuristics
   // it seems reasonable to think that half of the list might be freed though...
   if (!freedNodes){
      freedNodes = new LinkedList<void *>(DEFAULT_SIZE / 2);
   }

   freedNodes->addFirst((void *)oldNode);
}

// head->next points to the first element of the list
// head itself does not represent an element of the list.
// TODO - why isn't head just the first element or NULL otherwise?
//        find out why, and then change it here.
template<typename T>
void LinkedList<T>::addFirst(const T & element){

   struct LinkedList<T>::node * newNode = getNode();

   newNode->value = element;
   newNode->next = head->next;
   head->next = newNode;

   if(tail == head) tail = newNode;

   ++_length;

}

// tail actually is the last node of the list
template<typename T>
void LinkedList<T>::addLast(const T & element){

   struct LinkedList<T>::node * newNode = getNode();

   newNode->value = element;
   newNode->next = NULL;
   tail->next = newNode;
   tail = newNode;

   ++_length;

}

template <typename T>
T LinkedList<T>::peekFirst(){
   return head->next->value;
}

template <typename T>
T LinkedList<T>::popFirst(){
   T * temp = &(head->next->value);
   struct LinkedList<T>::node * tempNode = head->next;
   head->next = head->next->next;
   freeNode(tempNode);
   --_length;
   return *temp;
}

// Iterators!

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin(){
   return LinkedList<T>::iterator(head);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end(){
   return LinkedList<T>::iterator(tail);
}

// Insertions!!

template <typename T>
void LinkedList<T>::addAfter(const T& element, const LinkedList::iterator & position){
   struct LinkedList<T>::node * newNode = getNode();

   newNode->next = position.current->next->next;
   position.current->next->next = newNode;
   newNode->value = element;

   ++_length;
}

template <typename T>
void LinkedList<T>::addBefore(const T& element, LinkedList::iterator & position){
   struct LinkedList<T>::node * newNode = getNode();

   newNode->next = position.current->next;
   position.current->next = newNode;
   position.current = newNode;
   newNode->value = element;

   ++_length;
}

template <typename T>
void LinkedList<T>::remove(const LinkedList::iterator & position){
   struct LinkedList<T>::node * oldNode = position.current->next;

   position.current->next = position.current->next->next;

   freeNode(oldNode);

   --_length;
}

template <typename T>
size_t LinkedList<T>::length(){
   return _length;
}

template <typename T>
bool LinkedList<T>::empty(){
   return !_length;
}

