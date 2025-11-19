
#include <iostream>
#include "../../core/Edge.h"
#include "../../core/Node.h"
#include "../../render/Page/StatisticsPage.h"
#include "Dijkstra.h"
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

extern int ASTAR_VISITED;

int astarNodeVisited(const string &start, const string &end);

vector<string> astar(const string &start, const string &end);