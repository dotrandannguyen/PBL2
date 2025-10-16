#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

using namespace std;

// check mouseClick inside
bool isMouseInside(const SDL_Rect &rect, int mx, int my);

// Vẽ chữ
void renderText(SDL_Renderer *renderer, TTF_Font *font, const string &text, int x, int y, SDL_Color color);
