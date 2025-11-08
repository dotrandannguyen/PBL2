#include "AStar.h"

Node findNodeByID(const vector<Node> &nodes, const string &id)
{
    for (const auto &n : nodes)
    {
        if (n.getNodeID() == id)
        {
            return n;
        }
    }
    return Node();
}

float heuristic(const Node &a, const Node &b)
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

    unordered_map<string, Node> nodesMap;

    for (const auto &n : nodes)
        nodesMap[n.getNodeID()] = n;

    AdjList adj = buildAdjacencyList(edges, noFlyZones, nodesMap);

    const float INF = 1e9;

    unordered_map<string, float> rDist; // kc thưc
    unordered_map<string, float> fDist; // kc fake
    unordered_map<string, string> prev;
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> pq; // {khoang cach, nodeid}

    // chi lay node trong unorderer_map ra phần vector còn lai ko dùng
    for (const auto &[node, _] : adj)
    {
        rDist[node] = INF;
        fDist[node] = INF;
    }

    rDist[start] = 0.0f;
    fDist[start] = heuristic(findNodeByID(nodes, start), findNodeByID(nodes, end));
    pq.push({fDist[start], start}); // kc fake , start

    while (!pq.empty())
    {
        string nodeCurrent = pq.top().second;
        pq.pop();
        if (nodeCurrent == end)
        {
            break;
        } // tim thay duong

        for (const auto &[neighbor, cost] : adj[nodeCurrent])
        {
            float newkc = rDist[nodeCurrent] + cost;
            if (newkc < rDist[neighbor])
            {
                rDist[neighbor] = newkc;
                fDist[neighbor] = newkc + heuristic(findNodeByID(nodes, neighbor), findNodeByID(nodes, end));
                prev[neighbor] = nodeCurrent;
                pq.push({fDist[neighbor], neighbor});
            }
        }
    }
    // Truy ngược đường đi
    vector<string> path;

    for (string at = end; !at.empty(); at = prev.count(at) ? prev[at] : "")
        path.push_back(at);

    reverse(path.begin(), path.end());
    return path;
}
