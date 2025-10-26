#ifndef TASK_H
#define TASK_H

#include "Drone.h"
#include "Order.h"
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Task
{
private:
    Drone *ptr = nullptr;
    Order *ptr = nullptr;
    string TaskID;
    string DroneID;       // ref Drone.DroneID
    string OrderID;       // ref Order.OrderID
    string AlgorithmUsed; // AStar | Dijkstra
    float PathLength;
    float Duration;
    string Status; // assigned | completed

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
    void setTaskID(const string &taskId);
    void setDroneID(const string &droneId);
    void setOrderID(const string &orderId);
    void setAlgorithmUsed(const string &algo);
    void setPathLength(float pathLen);
    void setDuration(float duration);
    void setStatus(const string &status);
};

vector<Task> readTasksFromFile(const string &filename);
void writeTasksToFile(const string &filename, const vector<Task> &Tasks);

#endif
