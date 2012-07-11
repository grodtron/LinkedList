#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T>
class LinkedList {
   private:

      // the actual struct that is gonna be used in the list
      struct node{
         struct node * next;
         T & value;
      };

      // head of the data
      struct node * head;

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

   public:
      LinkedList();
     ~LinkedList();

      void addLast(T&);
      void addFirst(T&);
      void addAt(T&, int);

      T& removeFirst();
      T& removeLast();
      T& removeAt(int);

      T& getFirst();
      T& getLast();
      T& getAt(int);

      void setFirst(T&);
      void setLast(T&);
      void setAt(T&, int);
};

#endif