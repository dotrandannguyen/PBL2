#ifndef NOTIFICATIONPAGE_H
#define NOTIFICATIONPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iostream>
#include "../Renderer.h"

using namespace std;

void renderNotificationPage(SDL_Renderer *renderer, TTF_Font *font, const vector<string> &notifications);

#endif