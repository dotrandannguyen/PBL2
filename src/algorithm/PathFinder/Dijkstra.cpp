#include "Dijkstra.h"

using namespace std;

int DIJKSTRA_VISITED;

bool lineIntersectsCircle(float x1, float y1, float x2, float y2, float cx, float cy, float r)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    float fx = x1 - cx;
    float fy = y1 - cy;

    float a = dx * dx + dy * dy;
    float b = 2 * (fx * dx + fy * dy);
    float c = fx * fx + fy * fy - r * r;

    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
        return false; // không cắt

    discriminant = sqrt(discriminant);
    float t1 = (-b - discriminant) / (2 * a);
    float t2 = (-b + discriminant) / (2 * a);

    // kiểm tra điểm giao có nằm trên đoạn AB không
    return (t1 >= 0 && t1 <= 1) || (t2 >= 0 && t2 <= 1);
}

int dijkstraNodeVisited(const string &start, const string &end)
{
    // reset
    DIJKSTRA_VISITED = 0;

    vector<string> path = dijkstra(start, end);

    return DIJKSTRA_VISITED;
}

AdjList buildAdjacencyList(const vector<Edge> &edges, const vector<NoFlyZone> &zones, const unordered_map<string, Node> &nodesMap)
{
    AdjList adj;

    for (const auto &e : edges)
    {
        // --- kiểm tra Node tồn tại ---
        auto itA = nodesMap.find(e.getStartNode());
        auto itB = nodesMap.find(e.getEndNode());

        if (itA == nodesMap.end() || itB == nodesMap.end())
        {
            cerr << "Canh bao: NodeID "
                 << (itA == nodesMap.end() ? e.getStartNode() : e.getEndNode())
                 << " ko ton tai, bo canh "
                 << e.getStartNode() << " -> " << e.getEndNode() << "\n";
            continue; // bỏ cạnh, tránh out_of_range
        }

        Node a = itA->second;
        Node b = itB->second;

        // --- kiểm tra no-fly zone ---
        bool blocked = false;
        for (const auto &z : zones)
        {
            if (lineIntersectsCircle(a.getX(), a.getY(), b.getX(), b.getY(),
                                     z.x, z.y, z.r))
            {
                blocked = true;
                break;
            }
        }

        if (!blocked)
        {
            adj[e.getStartNode()].push_back({e.getEndNode(), e.getDistance()});
            adj[e.getEndNode()].push_back({e.getStartNode(), e.getDistance()});
        }
    }
    // ex
    // adj = {
    //     {"N01", {{"N02", 10.0}, {"N03", 5.0}}},
    //     {"N02", {{"N01", 10.0}, {"N04", 2.0}}}
    // };

    return adj;
}

vector<string> dijkstra(const string &start, const string &end)
{
    vector<Edge> edges = readEdgesFromFile("D:/Drone-project/src/data/Edge.txt");
    if (edges.empty())
    {
        cerr << "Khong the doc du lieu cạnh từ file.\n";
        return {};
    }

    unordered_map<string, Node> nodesMap;
    vector<Node> nodes = readNodesFromFile("D:/Drone-project/src/data/Node.txt");
    if (nodes.empty())
    {
        cerr << "Khong the doc du lieu node từ file.\n";
        return {};
    }
    for (const auto &n : nodes)
        nodesMap[n.getNodeID()] = n;

    AdjList adj = buildAdjacencyList(edges, noFlyZones, nodesMap);

    unordered_map<string, float> dist;                                                                 // dist[nodeid] = khoang cach tu start -> nodeid
    unordered_map<string, string> prev;                                                                // lu duong di ngan nhat theo dang N1 -> N2
    priority_queue<pair<float, string>, vector<pair<float, string>>, greater<pair<float, string>>> pq; // {khoang cach, nodeid}

    const float INF = 1e9;

    for (const auto &[node, _] : adj)
        dist[node] = INF; // set các cạnh ban đầu bằng vô hạn

    dist[start] = 0.0f; // khoang cach tu dinh start -> start = 0
    pq.push({0.0f, start});

    while (!pq.empty())
    {
        pair<float, string> top = pq.top();
        pq.pop();
        float kc = top.first;
        string u = top.second;
        if (kc > dist[u])
            continue; // da co duong ngan hon

        for (auto &[v, w] : adj.at(u)) // cách viết ngắn, tự tách pair<string,float> thành 2 biến
        {
            float newkc = kc + w;
            if (newkc < dist[v])
            {
                DIJKSTRA_VISITED++;
                dist[v] = newkc;
                prev[v] = u;
                pq.push({newkc, v});
            }
        }
    }

    // Truy ngược đường đi
    vector<string> path;
    if (dist[end] >= INF) // không có đường đi
        return path;

    for (string at = end; !at.empty(); at = prev.count(at) ? prev[at] : "")
        path.push_back(at);

    reverse(path.begin(), path.end());
    return path;
}