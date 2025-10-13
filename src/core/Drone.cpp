#include "Drone.h"
#include <iostream>

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
