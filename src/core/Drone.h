
#pragma once
#include <string>
#include <vector>
#include <cmath>
#include "Node.h"
using namespace std;

class Drone
{
private:
    string DroneID;
    string Name;
    float X, Y; // Thay vì string Position, dùng tọa độ x y
    float Speed;
    int Battery;
    string Status;
    string currentNodeID;

    // check drone da bay xong chua
    bool justFinished = false;

    // thêm biến phục vụ di chuyển
    vector<Node> path;
    int currentTargetIndex = 0;

public:
    Drone(string id = "", string name = "", float x = 0, float y = 0,
          float speed = 0, int battery = 0, string status = "", string currentNodeId = "");

    // Getter
    string getDroneID() const;
    string getName() const;
    float getX() const;
    float getY() const;
    float getSpeed() const;
    int getBattery() const;
    string getStatus() const;
    string getCurrentNodeID() const;
    bool getFinished() const;
    // Setter
    void setDroneID(const string &id);
    void setName(const string &name);
    void setPosition(float x, float y);
    void setSpeed(float speed);
    void setBattery(int battery);
    void setStatus(const string &status);
    void setCurrentNodeID(const string &id);
    void setFinished(const bool &value);

    void setPath(const vector<Node> &nodes);
    bool updateMove(float deltaTime);
};
vector<Drone> readDronesFromFile(const string &filename);
void writeDronesToFile(const string &filename, const vector<Drone> &drones);