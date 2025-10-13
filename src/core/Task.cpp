#include "Task.h"
#include <iostream>

Task::Task(string taskId, string droneId, string orderId, string algo, float pathLen, float duration, string status)
    : TaskID(taskId), DroneID(droneId), OrderID(orderId), AlgorithmUsed(algo), PathLength(pathLen), Duration(duration), Status(status) {}

string Task::getTaskID() const { return TaskID; }
string Task::getDroneID() const { return DroneID; }
string Task::getOrderID() const { return OrderID; }
string Task::getAlgorithmUsed() const { return AlgorithmUsed; }
float Task::getPathLength() const { return PathLength; }
float Task::getDuration() const { return Duration; }
string Task::getStatus() const { return Status; }

void Task::setTaskID(const string& taskId) { TaskID = taskId; }
void Task::setDroneID(const string& droneId) { DroneID = droneId; }
void Task::setOrderID(const string& orderId) { OrderID = orderId; }
void Task::setAlgorithmUsed(const string& algo) { AlgorithmUsed = algo; }
void Task::setPathLength(float pathLen) { PathLength = pathLen; }
void Task::setDuration(float duration) { Duration = duration; }
void Task::setStatus(const string& status) { Status = status; }

void Task::showInfo() const {
    cout << "TaskID: " << TaskID
         << "\nDroneID: " << DroneID
         << "\nOrderID: " << OrderID
         << "\nAlgorithmUsed: " << AlgorithmUsed
         << "\nPathLength: " << PathLength
         << "\nDuration: " << Duration
         << "\nStatus: " << Status << endl;
}
