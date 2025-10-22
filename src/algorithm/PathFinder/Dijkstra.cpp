#include "Dijkstra.h"

using namespace std;

AdjList buildAdjacencyList(const vector<Edge> &edges)
{
    AdjList adj;

    for (const auto &e : edges)
    {
        adj[e.getStartNode()].push_back({e.getEndNode(), e.getDistance()});
        adj[e.getEndNode()].push_back({e.getStartNode(), e.getDistance()}); // nếu vô hướng
    }

    return adj;
}

vector<string> dijkstra(const string &start, const string &end)
{
    vector<Edge> edges = readEdgesFromFile("D:/Drone-project/src/data/Edge.txt");
    if (edges.empty())
    {
        cerr << "Không thể đọc dữ liệu cạnh từ file.\n";
        return {};
    }

    AdjList adj = buildAdjacencyList(edges);

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
            continue;                  // da co duong ngan hon
        for (auto &[v, w] : adj.at(u)) // cách viết ngắn, tự tách pair<string,float> thành 2 biến
        {
            float newkc = kc + w;
            if (newkc < dist[v])
            {
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