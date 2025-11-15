#include "Hungarian.h"

using namespace std;

vector<int> hungarian(const vector<vector<float>> &costMatrix)
{
    int n = costMatrix.size();
    int m = costMatrix[0].size();
    int size = max(n, m);
    const float INF_COST = 1e9f;

    // Bổ sung ma trận thành vuông
    vector<vector<float>> cost(size, vector<float>(size, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cost[i][j] = costMatrix[i][j];

    vector<float> u(size + 1), v(size + 1);
    vector<int> p(size + 1), way(size + 1);

    for (int i = 1; i <= size; i++)
    {
        p[0] = i;
        int j0 = 0;
        vector<float> minv(size + 1, INF_COST);
        vector<char> used(size + 1, false);

        do
        {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            float delta = INF_COST;
            for (int j = 1; j <= size; j++)
            {
                if (used[j])
                    continue;
                float cur = cost[i0 - 1][j - 1] - u[i0] - v[j];
                if (cur < minv[j])
                {
                    minv[j] = cur;
                    way[j] = j0;
                }
                if (minv[j] < delta)
                {
                    delta = minv[j];
                    j1 = j;
                }
            }
            for (int j = 0; j <= size; j++)
            {
                if (used[j])
                {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                    minv[j] -= delta;
            }
            j0 = j1;
        } while (p[j0] != 0);

        // Hoàn nguyên đường
        do
        {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    vector<int> assignment(n, -1);
    for (int j = 1; j <= size; j++)
        if (p[j] <= n && j <= m)
            assignment[p[j] - 1] = j - 1;

    return assignment;
}

void assignOrdersHungarian(vector<Drone> &drones,
                           vector<Order> &orders,
                           const vector<Node> &nodes,
                           const vector<Edge> &edges)
{
    auto startTime = chrono::high_resolution_clock::now();
    // Lọc drone rảnh và order pending
    vector<int> idleIdx, pendingIdx;
    for (int i = 0; i < drones.size(); ++i)
        if (drones[i].getStatus() == "idle")
            idleIdx.push_back(i);

    for (int j = 0; j < orders.size(); ++j)
        if (orders[j].getStatus() == "pending")
            pendingIdx.push_back(j);

    int n = idleIdx.size();
    int m = pendingIdx.size();

    if (n == 0 || m == 0)
        return;

    const float INF_COST = 1e9f;
    vector<vector<float>> cost(n, vector<float>(m, INF_COST));

    // Bước 1: Xây dựng ma trận chi phí drone → order
    for (int i = 0; i < n; i++)
    {
        int di = idleIdx[i];
        Drone &d = drones[di];
        string start = findClosestNodeID(d, nodes);

        for (int j = 0; j < m; j++)
        {
            int oj = pendingIdx[j];
            Order &o = orders[oj];
            vector<string> path = astar(start, o.getPickupLocation());
            if (path.empty())
                continue;
            cost[i][j] = TotalPathDistance(path, edges);
        }
    }

        // Bước 2: Chạy Hungarian
    vector<int> assignment = hungarian(cost);

    // Bước 3: Gán và thiết lập đường đi

    for (int i = 0; i < n; i++)
    {
        int assignedCol = assignment[i];
        if (assignedCol == -1)
            continue;

        int droneIdx = idleIdx[i];
        int orderIdx = pendingIdx[assignedCol];

        if (cost[i][assignedCol] >= INF_COST / 2)
            continue;

        Drone &d = drones[droneIdx];
        Order &o = orders[orderIdx];

        // Xây dựng đường đi
        vector<string> path1 = astar(findClosestNodeID(d, nodes), o.getPickupLocation());
        vector<string> path2 = astar(o.getPickupLocation(), o.getDropoffLocation());

        vector<string> fullPath = path1;
        if (!path2.empty())
            fullPath.insert(fullPath.end(), path2.begin() + 1, path2.end());

        vector<Node> nodePath = convertPathToNodes(fullPath, nodes);
        d.setPath(nodePath);
        d.setStatus("moving");
        d.setAssignedOrderID(o.getOrderID());
        o.setStatus("moving");

        // Ghi thời gian xử lý (giống greedy)
        auto endTime = chrono::high_resolution_clock::now();
        float duration = chrono::duration<float, milli>(endTime - startTime).count();
        hungaryTimes.push_back(duration);
        cout << "[Hungarian] Drone " << droneIdx << " assigned to Order " << orderIdx
             << " in " << duration << " ms" << endl;
    }
}
