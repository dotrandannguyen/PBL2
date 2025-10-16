#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "D:/Drone-project/src/core/Drone.h"
#include "D:\Drone-project\src\render\Renderer.h"

extern bool isAddingDrone;

void renderHomePage(SDL_Renderer *renderer, TTF_Font *fontSmall, const std::vector<Drone> &drones);
SDL_Point getDronePosXY(const std::string &pos);
void handleHomePageClick(SDL_Renderer *renderer, int mx, int my, vector<Drone> &drones);
void handleAddDroneClick(int mx, int my, vector<Drone> &drones);
#endif
