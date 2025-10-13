#ifndef DRONE_H
#define DRONE_H

#include <string>
using namespace std;

class Drone
{
private:
    string DroneID; // Mã định danh drone
    string Name;
    string Position; // NodeID hiện tại
    float Speed;
    int Battery;
    string Status; // idle | busy | charging

public:
    Drone() = default;
    Drone(string id, string name, string pos, float speed, int battery, string status);

    // Getter
    string getDroneID() const;
    string getName() const;
    string getPosition() const;
    float getSpeed() const;
    int getBattery() const;
    string getStatus() const;

    // Setter
    void setDroneID(const string &id);
    void setName(const string &name);
    void setPosition(const string &pos);
    void setSpeed(float speed);
    void setBattery(int battery);
    void setStatus(const string &status);
};

#endif
