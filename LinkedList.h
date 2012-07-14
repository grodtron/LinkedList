#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iterator>

#define DEFAULT_SIZE 16

template <typename T>
class LinkedList {
   private:

      //////////////////////////////////////////////////////
      //                                                  //
      //                     Data Stuff                   //
      //                                                  //
      //////////////////////////////////////////////////////

      // the actual struct that is gonna be used in the list
      // TODO - look into templated typedefs
      // maybe it's just a "using"?
      struct node{
         struct node * next;
         T value;
      };

      // head of the data
      struct node * head;
      struct node * tail;

      // the length of the list
      // TODO - keep track of this and add methods to it:
      size_t _length;

      //////////////////////////////////////////////////////
      //                                                  //
      //                    Memory Stuff                  //
      //                                                  //
      //////////////////////////////////////////////////////

      LinkedList<void *> * allocatedBlocks;
      LinkedList<void *> * freedNodes;

      // keep track of how much space to allocate in the next block.
      // this should start at 1 and double each time
      int lastMemblockSize;

      // this is an array of nodes that are ready to use.
      struct node * currentAllocatedBlock;
      struct node * nextFreeNode;

      struct node * getNode();
      void freeNode(struct node *);

   public:

      class iterator : public std::iterator<std::forward_iterator_tag, T>{
         friend class LinkedList;
         private:
            struct LinkedList::node * current;

            iterator(LinkedList::node *);

         public:
            // construction and destruction
            iterator();
            // default destructor is fine because we don't
            // have any dynamically alocated memory

            // assignment and copy construction not needed
            // default is fine because we would just copy
            // the pointer anyways

            // incrementing
            LinkedList::iterator & operator++();
            LinkedList::iterator   operator++(int);

            // equality checking
            bool operator== (const LinkedList::iterator &);
            bool operator!= (const LinkedList::iterator &);

            // dereferencing
            T   operator*();
            T * operator->();
      };

      LinkedList(int size = DEFAULT_SIZE);
     ~LinkedList();

      LinkedList::iterator begin();
      LinkedList::iterator end();

      void addFirst(const T&);
      void addLast(const T&);

      T peekFirst();
      T popFirst();

      void addAfter(const T&, const LinkedList::iterator &);
      void addBefore(const T&, LinkedList::iterator &);

      void remove(const LinkedList::iterator &);

      size_t length();
      bool empty();
};

#include "LinkedList.cpp"
#include "LinkedList_iterator.cpp"

#endif
