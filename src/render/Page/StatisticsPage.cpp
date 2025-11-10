#include "StatisticsPage.h"

void renderStatisticsPage(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 100, 500, 600, 500);
    SDL_RenderDrawLine(renderer, 100, 500, 100, 100);
}