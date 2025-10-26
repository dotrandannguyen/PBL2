#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../../core/Drone.h"
#include "../Renderer.h"

void renderTaskPage(SDL_Renderer *renderer, TTF_Font *font, int startX);

#endif