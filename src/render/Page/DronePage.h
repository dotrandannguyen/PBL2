#ifndef DRONEPAGE_H
#define DRONEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "D:/Drone-project/src/core/Drone.h"

void renderDronePage(SDL_Renderer *renderer, TTF_Font *font, const std::vector<Drone> &drones, int startX);

#endif
