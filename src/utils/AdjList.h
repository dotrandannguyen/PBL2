// AdjList.h
#ifndef ADJLIST_H
#define ADJLIST_H
#include <unordered_map>
#include <vector>
#include <string>

using AdjList = std::unordered_map<std::string, std::vector<std::pair<std::string, float>>>;

#endif
