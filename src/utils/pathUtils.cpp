#include "PathUtils.h"

float TotalPathDistance(const vector<string> &path,
                        const vector<Edge> &edges)
{
    if (path.size() < 2)
        return 0.0f;

    float total = 0.0f;

    for (size_t i = 0; i + 1 < path.size(); i++)
    {
        const string &a = path[i];
        const string &b = path[i + 1];

        for (const auto &e : edges)
        {
            if ((e.getStartNode() == a && e.getEndNode() == b) ||
                (e.getStartNode() == b && e.getEndNode() == a))
            {
                total += e.getDistance();
                break;
            }
        }
    }

    return total;
}
