#ifndef NODE_H
#define NODE_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
  int key;
  Node *next;
  Node();
  Node(int new_key);
  ~Node();
};

class NodeC {
private:
public:
  char key;
  NodeC *next;
  NodeC(char new_key);
  ~NodeC();
};

class NodeD {
private:
public:
  double key;
  NodeD *next;
  NodeD(double new_key);
  ~NodeD();
};

#endif // NODE_H


