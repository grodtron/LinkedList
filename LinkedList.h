#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iterator>

#include <functional>

#define DEFAULT_SIZE 16

template <typename T>
class LinkedList {
   private:

      typedef struct node{
         struct node * next;
         T value;
      } node;

      // head of the data
      node * head;
      node * tail;

      // the length of the list
      size_t _length;

      LinkedList<void *> * allocatedBlocks;
      LinkedList<void *> * freedNodes;

      // keep track of how much space to allocate in the next block.
      // this should start at 1 and double each time
      int lastMemblockSize;

      // this is an array of nodes that are ready to use.
      node * currentAllocatedBlock;
      node * nextFreeNode;

      node * getNode();
      void freeNode(node *);

      void _quicksort(node * list, node ** ret_head, node ** ret_tail);
      template <typename Comparator>
      void _insertionsort(node * list, node ** ret_head, node ** ret_tail);
      template <typename Comparator>
      void _mergesort(node * list, node ** ret_head, node ** ret_tail);

   public:

      class iterator : public std::iterator<std::forward_iterator_tag, T>{
         friend class LinkedList;
         private:
            struct LinkedList::node * current;

            iterator(typename LinkedList::node *);

         public:
            // construction and destruction
            iterator();
            // default destructor is fine because we don't
            // have any dynamically alocated memory

            // assignment and copy construction not needed
            // default is fine because we would just copy
            // the pointer anyways

            // incrementing
            typename LinkedList::iterator & operator++();
            typename LinkedList::iterator   operator++(int);

            // equality checking
            bool operator== (const typename LinkedList::iterator &);
            bool operator!= (const typename LinkedList::iterator &);

            // dereferencing
            T   operator*();
            T * operator->();
      };

      LinkedList(int size = DEFAULT_SIZE);
     ~LinkedList();

      typename LinkedList::iterator begin();
      typename LinkedList::iterator end();

      void addFirst(const T&);
      void addLast(const T&);

      T peekFirst();
      T popFirst();

      void addAfter(const T&, const typename LinkedList::iterator &);
      void addBefore(const T&, typename LinkedList::iterator &);

      void remove(const typename LinkedList::iterator &);

      size_t length();
      bool empty();

      #ifdef __GXX_EXPERIMENTAL_CXX0X__
      template <typename Comparator=std::less<T> >
      #else
      template <typename Comparator>
      #endif
      void sort();
};

#include "LinkedList.cpp"
#include "LinkedList_iterator.cpp"
#include "LinkedList_sort.cpp"

#endif
