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
         T value;
      };

      // head of the data
      struct node * head;

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
            T & operator*();
            T * operator->();
      };

      LinkedList();
     ~LinkedList();

      // start off with a certain size
      LinkedList(int size);

      LinkedList::iterator begin();
      LinkedList::iterator end();

      void addFirst(const T&);
      void addLast(const T&);

      void addAfter(const T&, const LinkedList::iterator &);
      void addBefore(const T&, const LinkedList::iterator &);

      void remove(LinkedList::iterator &);

};

#endif
