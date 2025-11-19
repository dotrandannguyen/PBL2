
#ifndef HUNGARIAN_ASSIGNMENT_H
#define HUNGARIAN_ASSIGNMENT_H
#include <iostream>
#include <string>
#include <vector>
#include "../../core/Drone.h"
#include "../../core/Order.h"
#include "../../core/Node.h"
#include "../../core/Edge.h"
#include "../../core/Task.h"
#include "../PathFinder/AStar.h"
#include "../PathFinder/Dijkstra.h"
#include "Greedy.h"                           // Dùng lại các hàm findClosestNodeID, TotalPathDistance, convertPathToNodes
#include "../../render/Page/StatisticsPage.h" // hungaryTimes
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;

vector<int> hungarian(const vector<vector<float>> &costMatrix);

void assignOrdersHungarian(vector<Drone> &drones, vector<Order> &orders, const vector<Node> &nodes, const vector<Edge> &edges, vector<Task> &tasks);

#endif