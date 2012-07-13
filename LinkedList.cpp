#include "LinkedList.h"

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

// TODO - factor out acquiring a new free node to a seperate
// member function
//
// is it worth making this static? Adds a LOT of complexity to
// memory management....

template<typename T>
void LinkedList<T>::addFirst(T & element){

   struct LinkedList<T>::node * newNode;

   if(nextFreeNode <= lastFreeNode){
      newNode = nextFreeNode;
      ++nextFreeNode;
   }else{
      // TODO - allocate more memory
      // also have to make sure to check for failures to
      // allocate and then handle that somehow
   }

   newNode->value = element;
   newNode->next = head->next;
   head->next = newNode;

}

template<typename T>
void LinkedList<T>::addLast(T & element){

   struct LinkedList<T>::node * newNode;

   if(nextFreeNode <= lastFreeNode){
      newNode = nextFreeNode;
      ++nextFreeNode;
   }else{
      // TODO - allocate more memory
      // also have to make sure to check for failures to
      // allocate and then handle that somehow
   }

   newNode->value = element;
   newNode->next = NULL;
   tail->next = newNode;
   tail = newNode;

}

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iterator>

template <typename T>
class LinkedList {
   private:

      //////////////////////////////////////////////////////
      //                                                  //
      //                     Data Stuff                   //
      //                                                  //
      //////////////////////////////////////////////////////

      // the actual struct that is gonna be used in the list
      struct node{
         struct node * next;
         T & value;
      };

      // head of the data
      struct node * head;
      // head of the data
      struct node * tail;

      // the length of the list
      unsigned long length;

      //////////////////////////////////////////////////////
      //                                                  //
      //                    Memory Stuff                  //
      //                                                  //
      //////////////////////////////////////////////////////

      // this will make another internal linked list to manage
      // memory
      struct memnode{
         struct node * address;
         struct memnode * next;
      };
      
      // head of the memory list
      struct memnode * memhead;

      // keep track of how much space to allocate in the next block.
      // this should start at 1 and double each time
      int lastMemblockSize;

      // this is an array of nodes that are ready to use.
      struct node * nextFreeNode;
      struct node * lastFreeNode;

      // this will keep track of nodes that are incidentally freed.
      struct node * looseFreeNodes;

   public:



     ~LinkedList();

      LinkedList::iterator begin();
      LinkedList::iterator end();

      void addAfter(T&, const LinkedList::iterator &);
      void addBefore(T&, const LinkedList::iterator &);

      void remove(LinkedList::iterator &);

};

#endif
