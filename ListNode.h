#include <iostream>
using namespace std;

template <typename T>
class ListNode{
  public:

    T data;
    ListNode *next;
    ListNode *prev;

    ListNode();//constructor
    ListNode(T d);//overloaded constructor
    ~ListNode();
};

//implementation of list node class
template <typename T>
ListNode<T>::ListNode(){
  data = 0;
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::ListNode(T d)
{
  data = d;
  next = NULL;
  prev = NULL;
}

template <typename T>
ListNode<T>::~ListNode()
{
  if(next != NULL){
    delete next;
  }
  prev = NULL;
  next = NULL;
}
