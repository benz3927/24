#include "node.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;


// Node is a normal node with an integer key we made in class.
// It is used for our pointer-based Stack. NodeD is a node for doubles and NodeC is a node
// for charaacters. We need new nodes for each of these new classes for our different Stacks
// which respectively use the nodes Node, NodeC, and NodeD.

// Construct a node for ints
Node::Node() {
  key = 0;
  next = nullptr;
}

// Add a new node with a new key.
Node::Node(int new_key) {
  key = new_key;
  next = nullptr;
}

// Destructor for the node class.
Node::~Node() {
  delete next;
}

// Construct a node that holds characters
NodeC::NodeC(char new_key) {
  key = new_key;
  next = nullptr;
}

NodeC::~NodeC() {
  delete next;
}

//Construct a node that holds doubles.
NodeD::NodeD(double new_key) {
  key = new_key;
  next = nullptr;
}

NodeD::~NodeD() {
  delete next;
}