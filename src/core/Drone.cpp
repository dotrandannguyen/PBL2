
#include "Drone.h"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

Drone::Drone(string id, string name, float x, float y, float speed, int battery, string status)
    : DroneID(id), Name(name), X(x), Y(y), Speed(speed), Battery(battery), Status(status) {}

// Getter
string Drone::getDroneID() const { return DroneID; }
string Drone::getName() const { return Name; }
float Drone::getX() const { return X; }
float Drone::getY() const { return Y; }
float Drone::getSpeed() const { return Speed; }
int Drone::getBattery() const { return Battery; }
string Drone::getStatus() const { return Status; }

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

// Đọc file
vector<Drone> readDronesFromFile(const string &filename)
{
    vector<Drone> drones;
    ifstream file(filename);
    if (!file.is_open())
    {
        cerr << "Không thể mở file: " << filename << endl;
        return drones;
    }

    string id, name, status;
    float x, y, speed;
    int battery;

    while (file >> id >> name >> x >> y >> speed >> battery >> status)
    {
        drones.emplace_back(id, name, x, y, speed, battery, status);
    }

    file.close();
    return drones;
}

void Drone::setPath(const vector<Node> &nodes)
{
    path = nodes;
    currentTargetIndex = 0;
    if (!path.empty())
    {
        setPosition(path[0].getX(), path[0].getY());
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

    if (dist < 1.0f)
    {
        currentTargetIndex++;
        if (currentTargetIndex >= (int)path.size())
        {
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
    X += step * (dx / dist);
    Y += step * (dy / dist);
    return true;
}

// Ghi file
void writeDronesToFile(const string &filename, const vector<Drone> &drones)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Không thể ghi file: " << filename << endl;
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
             << d.getStatus() << "\n";
    }

    file.close();
}
