#include "Greedy.h"

string findClosestNodeID(const Drone &d, const vector<Node> &nodes)
{
    // cout << "[DEBUGFINDCLOSETNODEID]  findCloestNodeID duoc goi" << " ";
    float minDist = 1e9;
    string closestNodeID = "";

    for (const auto &n : nodes)
    {
        float dx = d.getX() - n.getX();
        float dy = d.getY() - n.getY();
        float dist = sqrt(dx * dx + dy * dy);
        if (dist < minDist)
        {
            minDist = dist;
            closestNodeID = n.getNodeID();
        }
    }

    // cout << closestNodeID << endl;
    return closestNodeID;
}

// ep drone ve node da set san

void snapDroneToNode(Drone &d, const vector<Node> &nodes)
{
    // cout << "[DEBUGSNAP] " << d.getDroneID() << " -> " << d.getCurrentNodeID() << endl;

    string targetID = d.getCurrentNodeID();
    if (targetID.empty())
    {
        targetID = findClosestNodeID(d, nodes);
    }

    for (const auto &n : nodes)
    {
        if (n.getNodeID() == targetID)
        {
            d.setPosition(n.getX(), n.getY());
            d.setCurrentNodeID(n.getNodeID());
            break;
        }
    }
}

float TotalPathDistance(const vector<string> &path, const vector<Edge> &edges)
{
    if (path.size() < 2)
        return 0.0f; //  nếu path chỉ 1 node hoặc rỗng => không có cạnh => dist = 0

    float total = 0.0f;

    for (int i = 0; i + 1 < path.size(); i++)
    {
        const string &a = path[i];
        const string &b = path[i + 1];

        for (const auto &e : edges)
        {
            if ((e.getStartNode() == a && e.getEndNode() == b) ||
                (e.getStartNode() == b && e.getEndNode() == a))
            {
                total += e.getDistance(); // cộng trọng số cạnh
                break;                    // tìm thấy cạnh tương ứng => thoát vòng edges
            }
        }
    }
    return total;
}

vector<Node> convertPathToNodes(const vector<string> &pathIDs, const vector<Node> &nodes)
{
    vector<Node> result;
    // Với mỗi nodeID trong pathIDs, tìm node tương ứng trong vector nodes
    for (const auto &id : pathIDs)
    {
        for (const auto &n : nodes)
        {
            if (n.getNodeID() == id)
            {
                result.push_back(n); // thêm Node thật vào kết quả
                break;
            }
        }
    }
    return result;
}

// void assignOrdersGreedy(vector<Drone> &drones, vector<Order> &orders, const vector<Node> &nodes, const vector<Edge> &edges)
// {
//     // cout << "[DEBUGDRONE] vi tri drone0 " << drones[0].getX() << " " << drones[0].getY() << endl;
//     // cout << "[DEBUGDRONE] vi tri drone1 " << drones[1].getX() << " " << drones[1].getY() << endl;
//     // cout << "[DEBUG] assignOrdersGreedy duoc goi!" << endl;
//     for (auto &order : orders)
//     {
//         if (order.getStatus() != "pending")
//             continue;

//         // lấy điểm lấy hàng và điểm giao hàng
//         string pickup = order.getPickupLocation();
//         string dropoff = order.getDropoffLocation();

//         float bestCost = INF;
//         int bestDroneIndex = -1;
//         vector<string> bestPathToPickUp; // luu path tu drone -> lay hang
//         for (int i = 0; i < (int)drones.size(); i++)
//         {
//             Drone &d = drones[i];
//             if (d.getStatus() != "idle")
//                 continue;

//             string start = findClosestNodeID(d, nodes);
//             // cout << "[DEBUGSTART]" << start << endl;
//             // lay toa do cau drone o node nao lam diem start -> sau nay bo sug class sau
//             // string start = d.getCurrentNodeID(); // Drone luôn nằm trên node

//             vector<string> path = astar(start, pickup); // tìm path từ node start -> diem lay hang

//             if (path.empty())
//                 continue;

//             float cost = TotalPathDistance(path, edges);

//             if (cost < bestCost)
//             {
//                 bestCost = cost;
//                 bestDroneIndex = i;
//                 bestPathToPickUp = path;
//             }
//         }

//         // Sau khi duyệt hết drone, nếu tìm được bestDroneIndex thì gán order
//         if (bestDroneIndex != -1)
//         {
//             // Lấy path từ pickup -> dropoff (để drone bay tiếp sau khi lấy hàng)
//             vector<string> pickupToDrop = astar(pickup, dropoff);

//             // Gộp path từ drone->pickup + pickup->dropoff
//             vector<string> fullPath = bestPathToPickUp;
//             if (!pickupToDrop.empty())
//             {
//                 fullPath.insert(fullPath.end(), pickupToDrop.begin() + 1, pickupToDrop.end());
//             }

//             // Chuyển fullPath (nodeID) sang vector<Node> để setPath cho drone
//             vector<Node> fullNodePath = convertPathToNodes(fullPath, nodes);

//             drones[bestDroneIndex].setPath(fullNodePath); // Drone lưu path để updateMove() dùng

//             // Cập nhật trạng thái
//             drones[bestDroneIndex].setStatus("moving");
//             order.setStatus("moving");
//         }
//     }
// }

void assignOrdersGreedy(vector<Drone> &drones, vector<Order> &orders, const vector<Node> &nodes, const vector<Edge> &edges)
{
    // với mỗi drone rảnh, tìm order pending gần nhất
    for (int i = 0; i < (int)drones.size(); ++i)
    {
        Drone &d = drones[i];
        if (d.getStatus() != "idle")
            continue; // chỉ xử lý drone rảnh

        string start = findClosestNodeID(d, nodes);
        float bestCost = INF;
        int bestOrderIndex = -1;
        vector<string> bestPathToPickUp;

        for (int j = 0; j < (int)orders.size(); ++j)
        {
            Order &order = orders[j];
            if (order.getStatus() != "pending")
                continue; // chỉ xét order chưa gán

            // path từ drone -> pickup
            vector<string> path = astar(start, order.getPickupLocation());
            if (path.empty())
                continue;

            float cost = TotalPathDistance(path, edges);
            if (cost < bestCost)
            {
                bestCost = cost;
                bestOrderIndex = j;
                bestPathToPickUp = path;
            }
        }

        if (bestOrderIndex != -1)
        {
            Order &o = orders[bestOrderIndex];
            // path pickup -> dropoff
            vector<string> pickupToDrop = astar(o.getPickupLocation(), o.getDropoffLocation());

            // gop path
            vector<string> fullPath = bestPathToPickUp;
            if (!pickupToDrop.empty())
            {
                fullPath.insert(fullPath.end(), pickupToDrop.begin() + 1, pickupToDrop.end());
            }

            vector<Node> fullNodePath = convertPathToNodes(fullPath, nodes);
            d.setPath(fullNodePath);
            d.setStatus("moving");
            o.setStatus("moving"); // đánh dấu order đã được gán
        }
    }
}
