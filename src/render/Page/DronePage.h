#ifndef DRONEPAGE_H
#define DRONEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iomanip>
#include "../../core/Drone.h"
#include "../Renderer.h"

void renderDronePage(SDL_Renderer *renderer, TTF_Font *font, const std::vector<Drone> &drones, int startX);

#endif
