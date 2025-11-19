#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <string>
#include <cmath>
#include "../Renderer.h"

using namespace std;

struct graphBoxes
{
    SDL_Rect boxes;
    vector<string> s;
    vector<float> line1;
    vector<float> line2;
};

extern vector<float> greedyTimes;
extern vector<float> hungaryTimes;
extern vector<float> astarVisited;
extern vector<float> dijkstraVisited;

void renderStatisticsPage(SDL_Renderer *renderer, TTF_Font *font, int startX);

#endif