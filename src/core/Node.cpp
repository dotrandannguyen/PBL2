#include "Node.h"
#include <iostream>
#include <fstream>

Node::Node(string id, string name, float x, float y)
    : NodeID(id), Name(name), X(x), Y(y) {}

string Node::getNodeID() const { return NodeID; }
string Node::getName() const { return Name; }
float Node::getX() const { return X; }
float Node::getY() const { return Y; }

void Node::setNodeID(const string &id) { NodeID = id; }
void Node::setName(const string &name) { Name = name; }
void Node::setPosition(float x, float y)
{
    X = x;
    Y = y;
}

vector<Node> readNodesFromFile(const string &filename)
{
    vector<Node> nodes;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Không thể mở file: " << filename << endl;
        return nodes;
    }

    string id, name;
    float x, y;

    while (file >> id >> name >> x >> y)
    {
        nodes.emplace_back(id, name, x, y);
    }

    file.close();
    return nodes;
}

// Ghi file
void writeNodesToFile(const string &filename, const vector<Node> &nodes)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Không thể ghi file: " << filename << endl;
        return;
    }

    for (const auto &n : nodes)
    {
        file << n.getNodeID() << " "
             << n.getName() << " "
             << n.getX() << " "
             << n.getY() << "\n";
    }

    file.close();
}