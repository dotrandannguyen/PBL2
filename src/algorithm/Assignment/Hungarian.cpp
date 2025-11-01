#include "Hungarian.h"

vector<int> hungarian(const vector<vector<float>> &costMatrix)
{
    int n = costMatrix.size();    // drones
    int m = costMatrix[0].size(); // orders
    int size = max(n, m);         // kích thước vuông hóa ma trận

    vector<vector<float>> cost(size, vector<float>(size, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cost[i][j] = costMatrix[i][j];
        }
    }
    // cost luc nay la ban sao cua costMatrix vs cac phan du ra bang 0

    // cac mang can de hoat dong
    vector<float> u(size + 1), v(size + 1); // hang va cot
    vector<int> p(size + 1), way(size + 1);
    // p: hang gan cho cot va nguoc lai
    // way: dò đường
    for (int i = 1; i <= size; i++)
    {
        p[0] = i;
        int j0 = 0;
        vector<float> minv(size + 1, INF);
        vector<char> used(size + 1, false);
        do
        {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            float delta = INF;
            for (int j = 1; j <= size; j++)
            {
                if (used[j])
                    continue;
                float curr = cost[i0 - 1][j - 1] - u[i0] - v[j];
                if (curr < minv[j])
                {
                    minv[j] = curr;
                    way[j] = j0;
                }
                if (minv[j] < delta)
                {
                    delta = minv[j];
                }
            }
        } while (p[j0] != 0);
    }
}

void assignOrdersHungarian(vector<Drone> &drones, vector<Order> &orders, const vector<Node> &nodes, const vector<Edge> &edges)
{
}