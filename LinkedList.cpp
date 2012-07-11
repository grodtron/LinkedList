#include "LinkedList.h"

template <typename T>
LinkedList<T>::LinkedList()
   : nextFreeNode(new LinkedList<T>::node), // TODO - do you need a [1] ? 
     lastFreeNode(nextFreeNode),
     head(new LinkedList<T>::node),
     memhead(new LinkedList<T>::memnode),
     lastMemblockSize(1)
{
   head->next = NULL;
   memhead->next = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
}
