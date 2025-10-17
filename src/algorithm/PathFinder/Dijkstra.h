
#include <iostream>
#include "../../core/Edge.h"

#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using AdjList = unordered_map<string, vector<pair<string, float>>>; // canh ke co dang {N1, weight}

vector<string> dijkstra(const AdjList &adj, const string &start, const string &end);