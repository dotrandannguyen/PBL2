#ifndef EDGE_H
#define EDGE_H

#include <string>
using namespace std;

class Edge {
private:
    int EdgeID;
    string StartNode;  // ref Node.NodeID
    string EndNode;    // ref Node.NodeID
    float Distance;

public:
    Edge() = default;
    Edge(int id, const string& start, const string& end, float distance);

    int getEdgeID() const;
    string getStartNode() const;
    string getEndNode() const;
    float getDistance() const;

    void setEdgeID(int id);
    void setStartNode(const string& start);
    void setEndNode(const string& end);
    void setDistance(float distance);

};

#endif
