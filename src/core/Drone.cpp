
#include "Drone.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

Drone::Drone(string id, string name, float x, float y, float speed, int battery, string status, string currentNodeID)
    : DroneID(id), Name(name), X(x), Y(y), Speed(speed), Battery(battery), Status(status), currentNodeID(currentNodeID) {}

// Getter
string Drone::getDroneID() const { return DroneID; }
string Drone::getName() const { return Name; }
float Drone::getX() const { return X; }
float Drone::getY() const { return Y; }
float Drone::getSpeed() const { return Speed; }
int Drone::getBattery() const { return Battery; }
string Drone::getStatus() const { return Status; }
string Drone::getCurrentNodeID() const { return currentNodeID; }
bool Drone::getFinished() const { return justFinished; }
string Drone::getAssignedOrderID() const { return assignedOrderID; }
// Setter
void Drone::setDroneID(const string &id) { DroneID = id; }
void Drone::setName(const string &name) { Name = name; }
void Drone::setPosition(float x, float y)
{
    X = x;
    Y = y;
}
void Drone::setSpeed(float speed) { Speed = speed; }
void Drone::setBattery(int battery) { Battery = battery; }
void Drone::setStatus(const string &status) { Status = status; }
void Drone::setCurrentNodeID(const string &id) { currentNodeID = id; }
void Drone::setFinished(const bool &value)
{
    justFinished = value;
}

void Drone::setAssignedOrderID(const string &id)
{
    assignedOrderID = id;
}

void Drone::setPath(const vector<Node> &nodes)
{
    path = nodes;
    currentTargetIndex = 0;

    if (!path.empty())
    {
        if (Status == "idle" || path.size() == 1)
        {
            setPosition(path[0].getX(), path[0].getY());
        }
        setStatus("moving");
    }
}

// Hàm updateMove(deltaTime)
bool Drone::updateMove(float deltaTime)
{

    if (Status != "moving" || path.empty() || currentTargetIndex >= (int)path.size())
        return false;

    Node target = path[currentTargetIndex];
    float dx = target.getX() - X;
    float dy = target.getY() - Y;
    float dist = sqrt(dx * dx + dy * dy);
    // cout << "[UPDATE MOVE] " << DroneID
    //      << " idx=" << currentTargetIndex
    //      << " pos=(" << X << "," << Y << ") "
    //      << " target=(" << target.getX() << "," << target.getY() << ") "
    //      << " dist=" << dist
    //      << " status=" << Status << endl;
    if (dist < 1.0f)
    {

        currentTargetIndex++;
        if (currentTargetIndex >= (int)path.size())
        {
            if (Status == "moving") // chỉ khi nó đang bay
            {
                justFinished = true; // đánh dấu là vừa hoàn tất
            }
            setStatus("idle");
            return false; // hết đường
        }
        target = path[currentTargetIndex];
        dx = target.getX() - X;
        dy = target.getY() - Y;
        dist = sqrt(dx * dx + dy * dy);
    }

    // Tính bước di chuyển (Speed pixel/s)
    float step = Speed * deltaTime;

    float oldX = X;
    float oldY = Y;
    X += step * (dx / dist);
    Y += step * (dy / dist);

    // Tính phần trăm pin hao mọt 200000.0fpx
    float moveDist = sqrt((X - oldX) * (X - oldX) + (Y - oldY) * (Y - oldY));

    float pinRateDist = 1.0f / 200000.0f;
    // float pinRateTime = 0.00002f;
    Battery -= moveDist * pinRateDist;

    if (Battery < 0)
        Battery = 0;

    // // --- Log sau khi cập nhật vị trí ---
    // cout << "[AFTER MOVE] " << DroneID
    //      << " newPos=(" << X << "," << Y << ")" << endl;
    // // ---------

    return true;
}

// Đọc file
vector<Drone> readDronesFromFile(const string &filename)
{
    // cout << "[DEBUG] readDronesFromFile() duoc goi!" << endl;
    vector<Drone> drones;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Khong the doc file: " << filename << endl;
        return drones;
    }

    string id, name, status;
    float x, y, speed;
    int battery;
    string currentNodeID;

    while (file >> id >> name >> x >> y >> speed >> battery >> status >> currentNodeID)
    {
        drones.emplace_back(id, name, x, y, speed, battery, status, currentNodeID);
    }

    file.close();
    return drones;
}

// Ghi file
void writeDronesToFile(const string &filename, const vector<Drone> &drones)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Khong the ghi file: " << filename << endl;
        return;
    }

    for (const auto &d : drones)
    {
        file << d.getDroneID() << " "
             << d.getName() << " "
             << d.getX() << " "
             << d.getY() << " "
             << d.getSpeed() << " "
             << d.getBattery() << " "
             << d.getStatus() << " " << d.getCurrentNodeID() << "\n";
    }

    file.close();
}
