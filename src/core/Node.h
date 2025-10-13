#ifndef NODE_H
#define NODE_H

#include <string>
using namespace std;

class Node {
private:
    string NodeID;
    string Name;
    int X;
    int Y;

public:
    Node() = default;
    Node(string id, string name, int x, int y);

    string getNodeID() const;
    string getName() const;
    int getX() const;
    int getY() const;

    void setNodeID(const string& id);
    void setName(const string& name);
    void setX(int x);
    void setY(int y);

};

#endif
