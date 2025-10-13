#include "Order.h"
#include <iostream>

Order::Order(string id, string pickup, string dropoff, float weight, string priority, string status)
    : OrderID(id), PickupLocation(pickup), DropoffLocation(dropoff), Weight(weight), Priority(priority), Status(status) {}

// Getter
string Order::getOrderID() const { return OrderID; }
string Order::getPickupLocation() const { return PickupLocation; }
string Order::getDropoffLocation() const { return DropoffLocation; }
float Order::getWeight() const { return Weight; }
string Order::getPriority() const { return Priority; }
string Order::getStatus() const { return Status; }

// Setter
void Order::setOrderID(const string &id) { OrderID = id; }
void Order::setPickupLocation(const string &pickup) { PickupLocation = pickup; }
void Order::setDropoffLocation(const string &dropoff) { DropoffLocation = dropoff; }
void Order::setWeight(float weight) { Weight = weight; }
void Order::setPriority(const string &priority) { Priority = priority; }
void Order::setStatus(const string &status) { Status = status;}
