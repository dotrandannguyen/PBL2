#ifndef GREEDY_ASSIGNMENT_H
#define GREEDY_ASSIGNMENT_H

#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

#include "../../core/Drone.h"
#include "../../core/Order.h"
#include "../../core/Task.h"
#include "../PathFinder/Dijkstra.h"
#include "../PathFinder/AStar.h"
#include "../../utils/pathUtils.h"
#include "../../render/Page/StatisticsPage.h"

using namespace std;

const float INF = 1e9f;

string findClosestNodeID(const Drone &d, const vector<Node> &nodes);

void snapDroneToNode(Drone &d, const vector<Node> &nodes);

float TotalPathDistance(const vector<string> &path, const vector<Edge> &edges);

vector<Node> convertPathToNodes(const vector<string> &pathIDs, const vector<Node> &nodes);

void assignOrdersGreedy(vector<Drone> &drones, vector<Order> &orders, const vector<Node> &nodes, const vector<Edge> &edges, vector<Task> &tasks);

#endif