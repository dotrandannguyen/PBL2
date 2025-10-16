#include "Drone.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Drone::Drone(string id, string name, string pos, float speed, int battery, string status)
    : DroneID(id), Name(name), Position(pos), Speed(speed), Battery(battery), Status(status) {}

// Getter
string Drone::getDroneID() const { return DroneID; }
string Drone::getName() const { return Name; }
string Drone::getPosition() const { return Position; }
float Drone::getSpeed() const { return Speed; }
int Drone::getBattery() const { return Battery; }
string Drone::getStatus() const { return Status; }

// Setter
void Drone::setDroneID(const string &id) { DroneID = id; }
void Drone::setName(const string &name) { Name = name; }
void Drone::setPosition(const string &pos) { Position = pos; }
void Drone::setSpeed(float speed) { Speed = speed; }
void Drone::setBattery(int battery) { Battery = battery; }
void Drone::setStatus(const string &status) { Status = status; }

vector<Drone> readDronesFromFile(const string &filename)
{
    vector<Drone> drones;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Không thể mở file: " << filename << endl;
        return drones;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string id, name, pos, speedStr, batteryStr, status;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, pos, ',');
        getline(ss, speedStr, ',');
        getline(ss, batteryStr, ',');
        getline(ss, status, ',');

        if (!id.empty())
        {
            drones.emplace_back(id, name, pos, stof(speedStr), stoi(batteryStr), status);
        }
    }

    file.close();
    return drones;
}

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
        file << d.getDroneID() << ","
             << d.getName() << ","
             << d.getPosition() << ","
             << d.getSpeed() << ","
             << d.getBattery() << ","
             << d.getStatus() << "\n";
    }

    file.close();
}