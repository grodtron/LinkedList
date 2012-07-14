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
      while(!allocatedBlocks->empty()){
         delete[] (LinkedList<T>::node *) allocatedBlocks->popFirst();
      }
      delete allocatedBlocks;
   }
   delete currentAllocatedBlock;
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
      // TODO - remove magic numbers
      if(nextFreeNode < currentAllocatedBlock){

         if(!allocatedBlocks) allocatedBlocks = new LinkedList<void *>;
         allocatedBlocks->addFirst((void *) currentAllocatedBlock);

         currentAllocatedBlock = new struct LinkedList<T>::node[DEFAULT_SIZE];

         nextFreeNode = currentAllocatedBlock + DEFAULT_SIZE - 1;
      }

      newNode = nextFreeNode;
      --nextFreeNode;
   }

   return newNode;
}

template<typename T>
void LinkedList<T>::freeNode(struct LinkedList<T>::node * oldNode){

   if(!freedNodes) freedNodes = new LinkedList<void *>(8);

   freedNodes->addFirst((void *)oldNode);
}

template<typename T>
void LinkedList<T>::addFirst(const T & element){

   struct LinkedList<T>::node * newNode = getNode();

   newNode->value = element;
   newNode->next = head->next;
   head->next = newNode;

   if(tail == head) tail = newNode;

   ++_length;

}

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

