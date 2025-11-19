#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>

#include "../core/Drone.h"
#include "../core/Node.h"
#include "../core/Order.h"
#include "../core/Edge.h"
#include "../core/Task.h"
#include "Page/StatisticsPage.h"
#include "../algorithm/PathFinder/AStar.h"
#include "../algorithm/PathFinder/Dijkstra.h"
#include "../algorithm/Assignment/Greedy.h"
#include "../algorithm/Assignment/Hungarian.h"

using namespace std;

// check mouseClick inside
bool isMouseInside(const SDL_Rect &rect, int mx, int my);

// Vẽ chữ
void renderText(SDL_Renderer *renderer, TTF_Font *font, const string &text, int x, int y, SDL_Color color);

// load texture from file
SDL_Texture *loadTexture(SDL_Renderer *renderer, const string &file);

void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h);
// Tính khoảng cách giữa 2 node
float calculateDistance(float x1, float y1, float x2, float y2);

void runAlgorithms(const vector<Drone> &drones,
                   const vector<Order> &orders,
                   const vector<Node> &nodes,
                   const vector<Edge> &edges,
                   const vector<Task> &tasks,
                   bool isAlgorithm);

#endif