#include "Edge.h"
#include <iostream>

Edge::Edge(int id, const string &start, const string &end, float distance)
    : EdgeID(id), StartNode(start), EndNode(end), Distance(distance) {}

int Edge::getEdgeID() const { return EdgeID; }
string Edge::getStartNode() const { return StartNode; }
string Edge::getEndNode() const { return EndNode; }
float Edge::getDistance() const { return Distance; }

void Edge::setEdgeID(int id) { EdgeID = id; }
void Edge::setStartNode(const string &start) { StartNode = start; }
void Edge::setEndNode(const string &end) { EndNode = end; }
void Edge::setDistance(float distance) { Distance = distance; }

// Ghi danh sách Edge vào file
void writeEdgesToFile(const string &filename, const vector<Edge> &edges)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Không thể ghi file: " << filename << endl;
        return;
    }

    for (const auto &e : edges)
    {
        file << e.getEdgeID() << " "
             << e.getStartNode() << " "
             << e.getEndNode() << " "
             << e.getDistance() << "\n";
    }

    file.close();
}

// Đọc danh sách Edge từ file
vector<Edge> readEdgesFromFile(const string &filename)
{
    vector<Edge> edges;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Không thể mở file: " << filename << endl;
        return edges;
    }

    int id;
    string start, end;
    float dist;

    while (file >> id >> start >> end >> dist)
    {
        edges.emplace_back(id, start, end, dist);
    }

    file.close();
    return edges;
}