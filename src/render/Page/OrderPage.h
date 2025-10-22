#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "../../core/Order.h"
#include "../Renderer.h"
using namespace std;

extern bool isAddingOrder;

void renderOrderPage(SDL_Renderer *renderer, TTF_Font *font, const std::vector<Order> &orders, int startX);

void handleAddOrder(vector<Order> &orders);