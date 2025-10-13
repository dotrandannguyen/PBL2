#include "Node.h"
#include <iostream>

Node::Node(string id, string name, int x, int y)
    : NodeID(id), Name(name), X(x), Y(y) {}

string Node::getNodeID() const { return NodeID; }
string Node::getName() const { return Name; }
int Node::getX() const { return X; }
int Node::getY() const { return Y; }

void Node::setNodeID(const string& id) { NodeID = id; }
void Node::setName(const string& name) { Name = name; }
void Node::setX(int x) { X = x; }
void Node::setY(int y) { Y = y; }



