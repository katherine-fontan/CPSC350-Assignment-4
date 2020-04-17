#include "DLinkedList.h"
#include <iostream>
using namespace std;

template<typename T>
class Queue{
  public:
    Queue();
    ~Queue();

    void insert(T d);
    T remove();
    T peek();
    int getSize();
    bool isEmpty();

    DLinkedList<T> *myQueue;

};

template<typename T>
Queue<T>::Queue(){
  myQueue = new DLinkedList<T>();
}

template<typename T>
Queue<T>::~Queue(){
  delete myQueue;
}

template<typename T>
void Queue<T>::insert(T d){
  myQueue->insertBack(d);
}

template<typename T>
T Queue<T>::remove(){
  if(myQueue->isEmpty())
    return NULL;

  return myQueue->removeFront();
}

template<typename T>
T Queue<T>::peek(){

  return myQueue->getFront();
}

template<typename T>
int Queue<T>::getSize()
{
  return myQueue->getSize();
}

template<typename T>
bool Queue<T>::isEmpty(){

  return myQueue->isEmpty();
}
