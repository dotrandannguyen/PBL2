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
    Drone *dronePtr = nullptr;
    Order *orderPtr = nullptr;
    string TaskID;
    string DroneID;       // ref Drone.DroneID
    string OrderID;       // ref Order.OrderID
    string AlgorithmUsed; // AStar | Dijkstra
    float PathLength;
    float Duration;
    string Status; // assigned | completed

public:
    Task() = default;

    Task(string taskId, Drone *d, Order *o, string algo, float pathLen, float duration, string status);
    // Constructor đọc file (chỉ lưu ID, chưa có con trỏ)
    Task(string taskId, string droneId, string orderId, string algo, float pathLen, float duration, string status);
    // Getter
    Drone *getDrone() const { return dronePtr; }
    Order *getOrder() const { return orderPtr; }
    string getTaskID() const;
    string getDroneID() const;
    string getOrderID() const;
    string getAlgorithmUsed() const;
    float getPathLength() const;
    float getDuration() const;
    string getStatus() const;

    // Setter
    void setDrone(Drone *d)
    {
        dronePtr = d;
        if (d)
            DroneID = d->getDroneID();
    }
    void setOrder(Order *o)
    {
        orderPtr = o;
        if (o)
            OrderID = o->getOrderID();
    }
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
void linkTasksWithPointers(vector<Task> &tasks, vector<Drone> &drones, vector<Order> &orders);

#endif
