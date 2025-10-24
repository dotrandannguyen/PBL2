#include "AStar.h"

Node findNodeByID(const vector<Node> &nodes, const string &id)
{
    for (const auto &n : nodes)
    {
        if (n.getNodeID() == id)
        {
            return n;
        }
        return Node();
    }
}

float heuristic(const Node &a, Node &b)
{
    float dx = a.getX() - b.getX();
    float dy = a.getY() - b.getY();
    return sqrt(dx * dx + dy * dy);
}

vector<string> astar(const string &start, const string &end)
{
    vector<Edge> edges = readEdgesFromFile("D:/Drone-project/src/data/Edge.txt");
    if (edges.empty())
    {
        cerr << "Khong de doc du lieu tu file.\n";
        return {};
    }
    vector<Node> nodes = readNodesFromFile("D:/Drone-project/src/data/Node.txt");
    if (nodes.empty())
    {
        cerr << "Khong de doc du lieu tu file.\n";
        return {};
    }

    AdjList adj = buildAdjacencyList(edges);

    const float INF = 1e9;
}