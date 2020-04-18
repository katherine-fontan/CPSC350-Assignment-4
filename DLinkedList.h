#include "ListNode.h"
#include <iostream>
using namespace std;

template <typename T>
class DLinkedList{
  public:
    DLinkedList();
    ~DLinkedList();

    ListNode<T> *front;
    ListNode<T> *back;

    int size;

    void insertFront(T d);
    void insertBack(T d);
    T getFront();
    T removeFront();
    T removeBack();
    T remove(T d);
    T removeAtPos(int pos);
    void printList();
    int find(T d); //search method
    bool isEmpty();
    int getSize();

};


template <typename T>
DLinkedList<T>::DLinkedList(){
  back = NULL;
  front = NULL;
  size = 0;
}

template <typename T>
DLinkedList<T>::~DLinkedList(){
  ListNode<T> *curr = front;
  while(size != 0){
    front = front->next;
    delete curr;
    size--;
  }
}

template <typename T>
void DLinkedList<T>::insertFront(T d){
  //make sure to check not an empty list
  ListNode<T> *node = new ListNode<T>(d);

  if(isEmpty()){
    front = node;
    back = node;
  }

  else{
    node -> next = front;
    front->prev = node;
    front = node;
  }

  size++;
}


template <typename T>
void DLinkedList<T>::insertBack(T d)
{
  //make sure to check not an empty list
  ListNode<T> *node = new ListNode<T>(d);
    if(isEmpty()){
      front = node;
      back = node;
    }
    else{
      node->prev = back;
      back->next = node;
      back = node;
    }
  size++;

}

template <typename T>
T DLinkedList<T>::getFront(){
  return front-> data;
}

template <typename T>
T DLinkedList<T>::removeFront(){
  if(isEmpty())
    return NULL;

  ListNode<T> *node = front;

  T temp = front->data;
  if(front->next != NULL){
    front->prev = NULL;
    front = front->next;
  }
  node->next = NULL;
  delete node;
  size--;

  return temp;
}

template <typename T>
T DLinkedList<T>::removeBack(){
  if(isEmpty())
    return NULL;

  ListNode<T> *node = back;

  T temp = back->data;


    back->prev->next = NULL;
    back = back->prev;
    node->prev = NULL;
    delete node;
    size--;
    return temp;

}

template <typename T>
T DLinkedList<T>::remove(T d){
  if(isEmpty())
    return NULL;

  ListNode<T> *curr = front;

  while(curr->data != d){
    curr = curr->next;
    if(curr == NULL)
      return NULL;
  }
  if(curr == front)
    front = curr ->next;

  else
    curr->prev->next = curr->next;

  if(curr == back)
    back = curr->prev;
  else
    curr->next->prev = curr->prev;

  curr->next = NULL;
  curr->prev = NULL;
  T temp = curr->date;
  size--;
  delete curr;

  return temp;
}

template <typename T>
T DLinkedList<T>::removeAtPos(int pos)
{
  //could call find() here
  //im going to search manually
  ListNode<T> *curr = front;
  int index = 0;

  while(index != pos){
    curr = curr->next;
    if(curr == NULL)
      return NULL;

    ++index;
  }
  if(curr == front)
    front = curr->next;

  else
    curr->prev->next = curr->next;

  if(curr == back)
    back = curr->prev;

  else
    curr->next->prev = curr->prev;

  curr->next = NULL;
  curr->prev =NULL;
  T d = curr->data;
  delete curr;
  size--;

  return d;
}

template <typename T>
void DLinkedList<T>::printList()
{
  ListNode<T> *curr = front;

  while(curr != NULL)
  {
    cout << curr-> data << endl;
    curr = curr -> next;
  }
  cout << endl;
}

template <typename T>
int DLinkedList<T>::find(T d)
{
  int index = -1;
  ListNode<T> *curr = front;

  while(curr != NULL){
    ++index;
    if(curr -> data == d){

      return ++index;
    }

      curr = curr -> next;
      ++index;
  }

  if(curr == NULL) //value does not exist in list
  {
    index = -1;
  }
  return index;
}

template <typename T>
bool DLinkedList<T>::isEmpty(){
  if(size == 0)
    return true;

  else
    return false;
}


template <typename T>
int DLinkedList<T>::getSize(){
  return size;
}
