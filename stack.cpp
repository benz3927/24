#include "stack.h"
#include "node.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

// Stack is the normal stack of integers we made in class, StackD is a stack of doubles, 
// and StackC is a stack of characters. The stacks are desgined to hold different classes 
// because each type of stack is needed for us to evaluate 
// and check a string expression if it evaluates to 24.

/**
* Constructs a new empty Stack.
* Initializes head pointer to null.
*/
Stack::Stack() {
  head = nullptr;
}

/**
* Checks if the stack is empty.
* @return true if stack is empty, false otherwise.
*/
bool Stack::empty() { return head == nullptr; }

/**
* Adds a new node with given key at the top of the stack.
* @param new_key the integer key value to be added.
*/
void Stack::push(int new_key) {
  Node *new_node = new Node(new_key);
  new_node->next = head;
  head = new_node;
}

/**
* Removes and returns the top item of the stack.
* @return the integer value of the popped element.
*/
int Stack::pop() {
  int item = head->key;
  head = head->next;
  return item;
}

/**
* Return the top element of the stack without removing it.
* @return the integer value of the top element.
*/
int Stack::top() {
  return head->key;
}

/**
* Return the index of the top element of the stack.
* @return the index of the top element.
*/
int Stack::top_index() {
  int index = 0;
  Node *current = head;
  while (current != nullptr) {
    index += 1;
    current = current->next;
  }
  return index - 1;
}

/**
* Destructs the stack and frees all the memory used by nodes.
* Deletes all the nodes in the linked list starting from head.
*/
Stack::~Stack() {
  Node *current = head;
  while (current != nullptr) {
    Node *temp = current;
    current = current->next;
    delete temp;
  }
}

StackC::StackC() { head = nullptr; }

bool StackC::empty() { return head == nullptr; }

void StackC::push(char new_key) {
  NodeC *new_node = new NodeC(new_key);
  new_node->next = head;
  head = new_node;
}

char StackC::top() {
  return head->key; }

char StackC::pop() {
  char item = head->key;
  head = head->next;
  return item;
}

StackC::~StackC() {
  NodeC *current = head;
  while (current != nullptr) {
    NodeC *temp = current;
    current = current->next;
    delete temp;
  }
}

StackD::StackD() { head = nullptr; }

bool StackD::empty() { return head == nullptr; }

void StackD::push(double new_key) {
  NodeD *new_node = new NodeD(new_key);
  new_node->next = head;
  head = new_node;
}

double StackD::top() {
  return head->key; }

double StackD::pop() {
  double item = head->key;
  head = head->next;
  return item;
}

StackD::~StackD() {
  NodeD *current = head;
  while (current != nullptr) {
    NodeD *temp = current;
    current = current->next;
    delete temp;
  }
}
