#ifndef HUNGARIAN_ASSIGNMENT_H
#define HUNGARIAN_ASSIGNMENT_H
#include <iostream>
#include <string>
#include <vector>
#include "../../core/Drone.h"
#include "../../core/Order.h"
#include "../../core/Node.h"
#include "../../core/Edge.h"

using namespace std;

const float INF = 1e9;

vector<int> hungarian(const vector<vector<float>> &costMatrix);

void assignOrdersHungarian(vector<Drone> &drones, vector<Order> &orders, const vector<Node> &nodes, const vector<Edge> &edges);

#endif