#include "LinkedList.h"

template <typename T>
LinkedList<T>::iterator::iterator(typename LinkedList::node * node) : current(node) {}

template <typename T>
LinkedList<T>::iterator::iterator() : LinkedList<T>::iterator(NULL) {}

// Increment

// pre
template <typename T>
typename LinkedList<T>::iterator & LinkedList<T>::iterator::operator++(){
   current = current->next;
   return * this;
}

// post
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::iterator::operator++(int){
   LinkedList<T>::iterator temp = LinkedList<T>::iterator(current);
   current = current->next;
   return temp;
}

// comparisons

template <typename T>
bool LinkedList<T>::iterator::operator== (const typename LinkedList<T>::iterator & other){
   return other.current == this->current;
}

template <typename T>
bool LinkedList<T>::iterator::operator!= (const typename LinkedList<T>::iterator & other){
   return other.current != this->current;
}

// dereference

template <typename T>
T LinkedList<T>::iterator::operator*(){
   return current->next->value;
}

template <typename T>
T * LinkedList<T>::iterator::operator->(){
   return &(current->next->value);
}
