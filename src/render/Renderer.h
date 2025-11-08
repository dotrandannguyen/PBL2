#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>

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