#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

class Order
{
private:
    string OrderID;
    string PickupLocation;
    string DropoffLocation;
    float Weight;
    string Priority; // low | normal | high
    string Status;   // pending | delivering | done

public:
    Order() = default;
    Order(string id, string pickup, string dropoff, float weight, string priority, string status);

    // Getter
    string getOrderID() const;
    string getPickupLocation() const;
    string getDropoffLocation() const;
    float getWeight() const;
    string getPriority() const;
    string getStatus() const;

    // Setter
    void setOrderID(const string &id);
    void setPickupLocation(const string &pickup);
    void setDropoffLocation(const string &dropoff);
    void setWeight(float weight);
    void setPriority(const string &priority);
    void setStatus(const string &status);

    void showInfo() const;
};

vector<Order> readOrdersFromFile(const string &filename);
void writeOrdersToFile(const string &filename, const Order &o);

#endif
