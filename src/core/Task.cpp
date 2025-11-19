#include "Task.h"
#include <fstream>
#include <sstream>

// Getters
Task::Task(const string &id, Drone *d, Order *o,
           const string &algo, float pathLen,
           float dura, const string &s)
    : TaskID(id), drone(d), order(o),
      algorithmUsed(algo), pathLength(pathLen),
      duration(dura), status(s) {}

string Task::getTaskID() const { return TaskID; }
Drone *Task::getDrone() const { return drone; }
Order *Task::getOrder() const { return order; }
string Task::getAlgorithmUsed() const { return algorithmUsed; }
float Task::getPathLength() const { return pathLength; }
float Task::getDuration() const { return duration; }
string Task::getStatus() const { return status; }

void Task::setTaskID(const string &id) { TaskID = id; }
void Task::setDrone(Drone *d) { drone = d; }
void Task::setOrder(Order *o) { order = o; }
void Task::setAlgorithmUsed(const string &algo) { algorithmUsed = algo; }
void Task::setPathLength(float pl) { pathLength = pl; }
void Task::setDuration(float dur) { duration = dur; }
void Task::setStatus(const string &stat) { status = stat; }

Task createTask(Drone *d, Order *o, const vector<string> &bestPathToPickUp,
                const vector<string> &pickupToDrop,
                float duration,
                vector<Edge> edges,
                int currentTaskCount)
{
    float dist1 = TotalPathDistance(bestPathToPickUp, edges);
    float dist2 = TotalPathDistance(pickupToDrop, edges);

    return Task(
        "T" + to_string(currentTaskCount + 1), // ID
        d,                                     // drone
        o,                                     // order
        "Greedy",                              // algorithm
        dist1 + dist2,                         // path length
        duration,                              // duration
        "assigned"                             // status
    );
}

vector<Task> readTasksFromFile(const string &filename,
                               vector<Drone> &drones,
                               vector<Order> &orders)
{
    vector<Task> tasks;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Khong the doc file: " << filename << endl;
        return tasks;
    }

    string taskID, droneID, orderID, algo, status;
    float pathLen, duration;

    while (file >> taskID >> droneID >> orderID >> algo >> pathLen >> duration >> status)
    {
        Task t;
        t.setTaskID(taskID);
        t.setAlgorithmUsed(algo);
        t.setPathLength(pathLen);
        t.setDuration(duration);
        t.setStatus(status);

        // gán drone*
        t.setDrone(nullptr);
        for (auto &d : drones)
            if (d.getDroneID() == droneID)
                t.setDrone(&d);

        // gán order*
        t.setOrder(nullptr);
        for (auto &o : orders)
            if (o.getOrderID() == orderID)
                t.setOrder(&o);

        tasks.push_back(t);
    }

    file.close();
    return tasks;
}

void writeTasksToFile(const string &filename, const vector<Task> &tasks)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Khong the ghi file: " << filename << endl;
        return;
    }

    for (const auto &t : tasks)
    {
        string droneID = t.getDrone() ? t.getDrone()->getDroneID() : "";
        string orderID = t.getOrder() ? t.getOrder()->getOrderID() : "";

        file << t.getTaskID() << " "
             << droneID << " "
             << orderID << " "
             << t.getAlgorithmUsed() << " "
             << t.getPathLength() << " "
             << t.getDuration() << " "
             << t.getStatus() << "\n";
    }

    file.close();
}