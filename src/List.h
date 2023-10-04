#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

/******************************************************************************************************
 * This class represents a linked list of node objects. Do not modify anything in the class interface *
 ******************************************************************************************************/
template <class T>
class List{

 private:
  Node<T> *start; //pointer to the first node in this list
  int mySize;  //size (or length) of this list

 public:
  List();
  ~List();
  int size();
  bool empty();
  void insertStart(T);
  void insertEnd(T);
  void insertAt(T, int);
  void removeStart();
  void removeEnd();
  void removeAt(int);
  T getFirst();
  T getLast();
  T getAt(int);
  int find(T);

  /*************************************************************************************************************************
   * Print the name and this list's size and values to stdout. This function is already implemented (no need to change it) *
   *************************************************************************************************************************/
  void print(string name){
    cout << name << ": ";
    cout << "size = " << size();
    cout << ", values = ";
    Node<T> *iterator = start;
    while(iterator != nullptr){
      cout << iterator->value << ' ';
      iterator = iterator->next;
    }
    cout << endl;
  }

}; //end of class interface (you may modify the code below)

/*************************************************************************************************************
 * Implement all the functions below. Construct an empty list by initializing this list's instance variables *
 *************************************************************************************************************/
template <class T>
List<T>::List() : start(nullptr), mySize(0){}
//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){ // responsible for deallocating memory for nodes included in the list
    Node<T> *curr = start;
    while(curr != nullptr){
        start = curr->next; // move start to next node in the list
        delete curr; // delete curr(current head node)
        curr = start; // set curr to next node in the list(ref: start = curr->next;)
    }
}

/********************************
 * Return the size of this list *
 ********************************/
template <class T>
int List<T>::size(){
    return mySize;
}

/**************************************************************
 * Return true if this list is empty. Otherwise, return false *
 **************************************************************/
template <class T>
bool List<T>::empty(){
    return start == nullptr;
}

/**********************************************************************************
 * Create a new node with value, and insert that new node into this list at start *
 **********************************************************************************/
template <class T>
void List<T>::insertStart(T value){
    Node<T> *newNode = new Node<T>(value);

    if(empty()){
        start = newNode;
    }
    else{
        newNode->next = start; // set newNode to point to current start in the list
        start = newNode; // start is now the newly inserted node in the list
    }
    mySize++;
}

/********************************************************************************
 * Create a new node with value, and insert that new node into this list at end *
 ********************************************************************************/
template <class T>
void List<T>::insertEnd(T value){
    Node<T> *newNode = new Node<T>(value);

    if(empty()){
        start = newNode;
    }
    else{
        Node<T> *curr = start;
        while(curr->next != nullptr){ 
            curr = curr->next; // traversing
        }
        curr->next = newNode;
    }
    mySize++;
}

/********************************************************************************
 * Create a new node with value <value>, and insert that new node at position j *
 ********************************************************************************/
template <class T>
void List<T>::insertAt(T value, int j){
    Node<T> *newNode = new Node<T>(value);
    if(empty() || j > mySize || j < 0){
        delete newNode; // deallocate memory; destructor will NOT deallocate since it's not part of the list
        return;
    }
    else if(j == 0){ // in the case where j is at position of start
        newNode->next = start; // insert node at beginning of the list
        start = newNode;
        mySize++;
    }
    else{ // insert node at middle or end of the list
        Node<T> *curr = start;
        int currPos = 0;
        while(currPos < j - 1){ // stop at node before node at position j
            curr = curr->next; // traversing
            currPos++;
        }
    // valid position j: place node at position j
    newNode->next = curr->next; // new node points to where curr points
    curr->next = newNode;
    mySize++;
    }
}

/*******************************************************
 * Remove node at start; make no other changes to list *
 *******************************************************/
template <class T>
void List<T>::removeStart(){
    if(empty()){
        return;
    }
    Node<T> *curr = start;
    start = curr->next;
    delete curr;
    mySize--;
}

/*****************************************************
 * Remove node at end; make no other changes to list *
 *****************************************************/
template <class T>
void List<T>::removeEnd(){
    if(empty()){
        return;
    }
    if(start->next == nullptr){ // one node in the list
        delete start;
        start = nullptr;
        mySize--;
    }
    else{
        Node<T> *curr = start;
        while(curr->next->next != nullptr){ // stop at second to last node
            curr = curr->next; // traversing
        }
    delete curr->next; // deleting last node in the list
    curr->next = nullptr;
    mySize--;
    }
}

/************************************************************
 * Remove node at position j; make no other changes to list *
 ************************************************************/
template <class T>
void List<T>::removeAt(int j){
    if(empty() || j >= mySize){ // list is empty or j is out of bounds
        return;
    }
    else if(j == 0){ // j is equal to start position(start node)
        Node<T> *temp = start;
        start = start->next;
        delete temp;
        mySize--;
    }
    else{
        int currPos = 0;
        Node<T> *curr = start;
        while(currPos < j - 1){ // j - 1: since curr = curr->next, stop at node before node at j
            curr = curr->next;
            currPos++;
        }
    // position j is a valid position
    Node<T> *temp = curr->next;
    curr->next = temp->next; // skips the node at pos j
    delete temp;
    mySize--;
    }
}

/**********************************************************************************************************************
 * Return the value of the first node in the Linked List. If no first node, return the default constructed value: T() *
 **********************************************************************************************************************/
template <class T>
T List<T>::getFirst(){
    return empty() ? T() : start->value;
}

/*********************************************************************************************************************
 * Return the value of the last node in the Linked List. If no first node, return the default constructed value: T() *
 *********************************************************************************************************************/
template <class T>
T List<T>::getLast(){
    if(empty()){
        return T();
    }
    Node<T> *curr = start;
    while(curr->next != nullptr){
        curr = curr->next;
    }
    return curr->value;
}

/******************************************************************************************************************************
 * Return the value of the node at position j in the Linked List. If no first node, return the default constructed value: T() *
 ******************************************************************************************************************************/
template <class T>
T List<T>::getAt(int j){
    if(empty() || j < 0 || j >= mySize){
        return T();
    }
    int currPos = 0;
    Node<T> *curr = start;

    while(currPos < j){
        curr = curr->next;
        currPos++;
    }
    return curr->value;
}

/*************************************************************************************************
 * Return the position of the (first) node whose value is equal to the key. Otherwise, return -1 *
 *************************************************************************************************/
template <class T>
int List<T>::find(T key){
    if(empty()){
        return -1;
    }
    int currPos = 0;
    Node<T> *curr = start;

    while(curr != nullptr){
        if(curr->value == key){
            return currPos;
        }
        curr = curr->next;
        currPos++;
    }
    return -1;
}
