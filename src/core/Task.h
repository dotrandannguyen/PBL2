#ifndef TASK_H
#define TASK_H
#include <iostream>
#include <string>
#include "Drone.h"
#include "Order.h"
#include "Edge.h"
#include "../utils/pathUtils.h"
#include "../utils/AdjList.h"

using namespace std;

class Task
{
private:
    string TaskID;
    Drone *drone;
    Order *order;
    string algorithmUsed;
    float pathLength;
    float duration;
    string status;

public:
    Task(const string &id = "", Drone *d = nullptr, Order *o = nullptr, const string &algo = "", float pathLen = 0.0f, float dura = 0.0f, const string &s = "");
    // getter
    string getTaskID() const;
    Drone *getDrone() const;
    Order *getOrder() const;
    string getAlgorithmUsed() const;
    float getPathLength() const;
    float getDuration() const;
    string getStatus() const;

    // setter
    void setTaskID(const string &id);
    void setDrone(Drone *d);
    void setOrder(Order *o);
    void setAlgorithmUsed(const string &algo);
    void setPathLength(float pathLength);
    void setDuration(float duration);
    void setStatus(const string &status);
};

Task createTask(Drone *d, Order *o, const vector<string> &bestPathToPickUp,
                const vector<string> &pickupToDrop,
                float duration,
                vector<Edge> edges,
                int currentTaskCount);

vector<Task> readTasksFromFile(const string &filename,
                               vector<Drone> &drones,
                               vector<Order> &orders);
void writeTasksToFile(const string &filename, const vector<Task> &tasks);
#endif