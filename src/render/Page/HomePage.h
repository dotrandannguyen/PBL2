#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "../../core/Drone.h"
#include "../../core/Node.h"
#include "../../core/Edge.h"
#include "../../core/Order.h"
#include "../Renderer.h"
using namespace std;

extern bool isAddingDrone;
extern bool isAddingNode;
extern bool showInfoPanel;

void renderHomePage(SDL_Renderer *renderer, TTF_Font *fontSmall, const vector<Drone> &drones, const vector<Node> &nodes, const vector<Edge> &edges, const vector<Order> &orders);
SDL_Point getDronePosXY(const string &pos);

void handleHomePageDroneClick(SDL_Renderer *renderer, int mx, int my, vector<Drone> &drones, const vector<Node> &nodes);
// void handleAddDroneClick(int mx, int my, vector<Drone> &drones);
void hanldeHomePageInfoClick(SDL_Renderer *renderer, int mx, int my);
void handleHomePageNodeClick(SDL_Renderer *renderer, int mx, int my);
void handleAddNodeClick(int mx, int my, vector<Node> &nodes, vector<Edge> &edges);
#endif
