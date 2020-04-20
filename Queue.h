#include "DLinkedList.h"
#include <iostream>
using namespace std;

template<typename T>
class GenQueue{
  public:
    GenQueue();
    ~GenQueue();

    void insert(T d);
    T remove();
    T peek();
    int getSize();
    bool isEmpty();

    DLinkedList<T> *myQueue;

};

template<typename T>
GenQueue<T>::GenQueue(){
  myQueue = new DLinkedList<T>();
}

template<typename T>
GenQueue<T>::~GenQueue(){
  delete myQueue;
}

template<typename T>
void GenQueue<T>::insert(T d){
  myQueue->insertBack(d);
}

template<typename T>
T GenQueue<T>::remove(){
  if(myQueue->isEmpty())
    return NULL;

  return myQueue->removeFront();
}

template<typename T>
T GenQueue<T>::peek(){

  return myQueue->getFront();
}

template<typename T>
int GenQueue<T>::getSize()
{
  return myQueue->getSize();
}

template<typename T>
bool GenQueue<T>::isEmpty(){

  return myQueue->isEmpty();
}
