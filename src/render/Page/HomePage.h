#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "../../core/Drone.h"
#include "../../core/Node.h"
#include "../../core/Edge.h"
#include "../Renderer.h"

extern bool isAddingDrone;
extern bool isAddingNode;

void renderHomePage(SDL_Renderer *renderer, TTF_Font *fontSmall, const std::vector<Drone> &drones, const std::vector<Node> &nodes, const std::vector<Edge> &edges);
SDL_Point getDronePosXY(const std::string &pos);
void handleHomePageDroneClick(SDL_Renderer *renderer, int mx, int my, vector<Drone> &drones, const vector<Node> &nodes);
// void handleAddDroneClick(int mx, int my, vector<Drone> &drones);

void handleHomePageNodeClick(SDL_Renderer *renderer, int mx, int my);
void handleAddNodeClick(int mx, int my, vector<Node> &nodes, vector<Edge> &edges);
#endif
