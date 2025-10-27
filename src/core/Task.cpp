#include "Task.h"

Task::Task(string taskId, Drone *d, Order *o, string algo, float pathLen, float duration, string status)
    : TaskID(taskId),
      dronePtr(d),
      orderPtr(o),
      DroneID(d ? d->getDroneID() : ""),
      OrderID(o ? o->getOrderID() : ""),
      AlgorithmUsed(algo),
      PathLength(pathLen),
      Duration(duration),
      Status(status) {}

Task::Task(string taskId, string droneId, string orderId, string algo, float pathLen, float duration, string status)
    : TaskID(taskId),
      DroneID(droneId),
      OrderID(orderId),
      AlgorithmUsed(algo),
      PathLength(pathLen),
      Duration(duration),
      Status(status),
      dronePtr(nullptr),
      orderPtr(nullptr) {}

string Task::getTaskID() const { return TaskID; }
string Task::getDroneID() const { return DroneID; }
string Task::getOrderID() const { return OrderID; }
string Task::getAlgorithmUsed() const { return AlgorithmUsed; }
float Task::getPathLength() const { return PathLength; }
float Task::getDuration() const { return Duration; }
string Task::getStatus() const { return Status; }

void Task::setTaskID(const string &taskId) { TaskID = taskId; }
void Task::setDroneID(const string &droneId) { DroneID = droneId; }
void Task::setOrderID(const string &orderId) { OrderID = orderId; }
void Task::setAlgorithmUsed(const string &algo) { AlgorithmUsed = algo; }
void Task::setPathLength(float pathLen) { PathLength = pathLen; }
void Task::setDuration(float duration) { Duration = duration; }
void Task::setStatus(const string &status) { Status = status; }

vector<Task> readTasksFromFile(const string &filename)
{
    vector<Task> tasks;
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the doc duoc file task: " << filename << endl;
        return tasks;
    }

    string task_id, drone_id, order_id, algorithm, status;
    float path_length, duration;
    while (file >> task_id >> drone_id >> order_id >> algorithm >> path_length >> duration >> status)
    {
        tasks.emplace_back(task_id, drone_id, order_id, algorithm, path_length, duration, status);
    }

    file.close();
    return tasks;
}

void writeTasksToFile(const string &filename, const vector<Task> &tasks)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the ghi file: " << filename << endl;
        return;
    }

    for (const auto &t : tasks)
    {
        file << t.getTaskID() << " "
             << t.getDroneID() << " "
             << t.getOrderID() << " "
             << t.getAlgorithmUsed() << " "
             << t.getPathLength() << " "
             << t.getDuration() << " "
             << t.getStatus() << "\n";
    }
    file.close();
}

// Liên kết lại con trỏ Task <-> Drone, Order sau khi đọc file
void linkTasksWithPointers(vector<Task> &tasks, vector<Drone> &drones, vector<Order> &orders)
{
    for (auto &task : tasks)
    {
        for (auto &d : drones)
        {
            if (d.getDroneID() == task.getDroneID())
            {
                task.setDrone(&d);
                break;
            }
        }

        for (auto &o : orders)
        {
            if (o.getOrderID() == task.getOrderID())
            {
                task.setOrder(&o);
                break;
            }
        }
    }
}