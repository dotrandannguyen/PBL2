#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include "../Renderer.h"

using namespace std;

struct graphBoxes
{
    SDL_Rect boxes;
    vector<string> s;
};

void renderStatisticsPage(SDL_Renderer *renderer, TTF_Font *font, int startX);

#endif