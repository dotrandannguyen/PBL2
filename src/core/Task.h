#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task {
private:
    string TaskID;
    string DroneID;    // ref Drone.DroneID
    string OrderID;    // ref Order.OrderID
    string AlgorithmUsed; // AStar | Dijkstra
    float PathLength;
    float Duration;
    string Status;     // assigned | completed

public:
    Task() = default;
    Task(string taskId, string droneId, string orderId, string algo, float pathLen, float duration, string status);

    // Getter
    string getTaskID() const;
    string getDroneID() const;
    string getOrderID() const;
    string getAlgorithmUsed() const;
    float getPathLength() const;
    float getDuration() const;
    string getStatus() const;

    // Setter
    void setTaskID(const string& taskId);
    void setDroneID(const string& droneId);
    void setOrderID(const string& orderId);
    void setAlgorithmUsed(const string& algo);
    void setPathLength(float pathLen);
    void setDuration(float duration);
    void setStatus(const string& status);

};

#endif
