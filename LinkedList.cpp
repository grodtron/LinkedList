#include "LinkedList.h"

#include <cassert>

#define DEFAULT_SIZE 8

// construct a list of a given size
template <typename T>
LinkedList<T>::LinkedList(int size)
   : nextFreeNode(new LinkedList<T>::node[size]),
     lastFreeNode(nextFreeNode + (size - 1)),
     head(new LinkedList<T>::node),
     tail(head),
     memhead(new LinkedList<T>::memnode),
     lastMemblockSize(size)
{
   head->next = NULL;
   memhead->next = NULL;
   looseFreeNodes = NULL;
}

// construct a list of default size
template <typename T>
LinkedList<T>::LinkedList() : LinkedList(DEFAULT_SIZE) {}

template <typename T>
LinkedList<T>::~LinkedList()
{
   // TODO
}

template<typename T>
struct LinkedList<T>::node * LinkedList<T>::getNode(){

   struct LinkedList<T>::node * newNode;

   // first check in our list of random
   if(looseFreeNodes){

      newNode = looseFreeNodes;
      looseFreeNodes = newNode->next;

   // then if not, take it from our current block
   }else if(nextFreeNode <= lastFreeNode){

      newNode = nextFreeNode;
      ++nextFreeNode;
   }
}

template<typename T>
void LinkedList<T>::returnNode(struct LinkedList<T>::node * oldNode){

   // keep a nice little list of free nodes ready to be reused
   oldNode->next = looseFreeNodes->next;
   looseFreeNodes = oldNode;
}

template<typename T>
void LinkedList<T>::addFirst(const T & element){

   struct LinkedList<T>::node * newNode = getNode();

   newNode->value = element;
   newNode->next = head->next;
   head->next = newNode;

}

template<typename T>
void LinkedList<T>::addLast(const T & element){

   struct LinkedList<T>::node * newNode = getNode();


   newNode->value = element;
   newNode->next = NULL;
   tail->next = newNode;
   tail = newNode;

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
}

template <typename T>
void LinkedList<T>::addBefore(const T& element, const LinkedList::iterator & position){
   struct LinkedList<T>::node * newNode = getNode();

   newNode->next = position.current->next;
   position.current->next = newNode;
   position.current = newNode;
   newNode->value = element;
}

template <typename T>
void LinkedList<T>::remove(const LinkedList::iterator & position){
   struct LinkedList<T>::node * oldNode = position.current->next;

   position.current->next = position.current->next->next;

   returnNode(oldNode);
}

