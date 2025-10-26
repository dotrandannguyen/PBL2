#include "Task.h"

Task::Task(string taskId, string droneId, string orderId, string algo, float pathLen, float duration, string status)
    : TaskID(taskId), DroneID(droneId), OrderID(orderId), AlgorithmUsed(algo), PathLength(pathLen), Duration(duration), Status(status) {}

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
        cout << "khong the doc duoc file task: " << filename << endl;
        return tasks;
    }

    string task_id, drone_id, order_id, algorithm, status;
    float path_length, duration;
    while (file >> task_id >> drone_id >> order_id >> algorithm >> path_length >> duration >> status)
    {
        tasks.emplace_back(task_id, drone_id, order_id, algorithm, path_length, duration, status);
    }
    // emplace_back tiết kiệm bước tạo tạm, trực tiếp dựng đối tượng trong vector → nhanh hơn và gọn hơn.
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