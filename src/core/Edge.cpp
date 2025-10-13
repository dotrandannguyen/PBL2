#include "Edge.h"
#include <iostream>

Edge::Edge(int id, const string& start, const string& end, float distance)
    : EdgeID(id), StartNode(start), EndNode(end), Distance(distance) {}

int Edge::getEdgeID() const { return EdgeID; }
string Edge::getStartNode() const { return StartNode; }
string Edge::getEndNode() const { return EndNode; }
float Edge::getDistance() const { return Distance; }

void Edge::setEdgeID(int id) { EdgeID = id; }
void Edge::setStartNode(const string& start) { StartNode = start; }
void Edge::setEndNode(const string& end) { EndNode = end; }
void Edge::setDistance(float distance) { Distance = distance; }

