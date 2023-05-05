#ifndef STACK_H
#define STACK_H

#include "node.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Stack {
private:
  Node *head;

public:
  Stack();
  bool empty();
  void push(int new_key);
  int pop();
  int top();
  int top_index();
  ~Stack();
};

class StackC {
private:
  NodeC *head;

public:
  StackC();
  bool empty();
  void push(char new_key);
  char pop();
  char top();
  ~StackC();
};

class StackD {
private:
  NodeD *head;

public:
  StackD();
  bool empty();
  void push(double new_key);
  double pop();
  double top();
  ~StackD();
};

#endif // STACK_H


