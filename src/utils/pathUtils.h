#ifndef PATH_UTILS_H
#define PATH_UTILS_H

#include <vector>
#include <string>
#include "../core/Edge.h"

float TotalPathDistance(const std::vector<std::string> &path,
                        const std::vector<Edge> &edges);

#endif
