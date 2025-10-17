#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>

using namespace std;

class Node
{
private:
    string NodeID;
    string Name;
    float X, Y;

public:
    Node() = default;
    Node(string id, string name, float x, float y);

    // Getter
    string getNodeID() const;
    string getName() const;
    float getX() const;
    float getY() const;

    // Setter
    void setNodeID(const string &id);
    void setName(const string &name);
    void setPosition(float x, float y); // Set X và Y cùng lúc
};

vector<Node> readNodesFromFile(const string &filename);
void writeNodesToFile(const string &filename, const vector<Node> &nodes);

#endif
