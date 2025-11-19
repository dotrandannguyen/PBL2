#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "../../core/Task.h"
#include "../Renderer.h"

using namespace std;

void renderTaskPage(SDL_Renderer *renderer, TTF_Font *font, const vector<Task> tasks, int startX);

#endif