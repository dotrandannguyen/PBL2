#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include "../../core/Edge.h"
#include "../../core/Node.h"
#include "../../render/Page/HomePage.h"
#include "../../render/Page/StatisticsPage.h"
#include "../../utils/NoFLyZone.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using AdjList = unordered_map<string, vector<pair<string, float>>>; // canh ke co dang {N1, {N2, weight}}

extern int DIJKSTRA_VISITED;

int dijkstraNodeVisited(const string &start, const string &end);

AdjList buildAdjacencyList(const vector<Edge> &edges, const vector<NoFlyZone> &zones, const unordered_map<string, Node> &nodesMap);

vector<string> dijkstra(const string &start, const string &end);

#endif
