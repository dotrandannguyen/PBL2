#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include "../../core/Drone.h"
#include "../../core/Node.h"
#include "../../core/Edge.h"
#include "../../core/Order.h"
#include "../../algorithm/Assignment/Greedy.h"
#include "../Renderer.h"
using namespace std;

extern bool isAddingOrder;

struct OrderButton
{
    SDL_Rect editBtn;
    SDL_Rect delBtn;
    string OrderID;
};

extern vector<OrderButton> orderButtons;

void renderOrderPage(SDL_Renderer *renderer, TTF_Font *font, const vector<Order> &orders, int startX);

void handleAddOrder(vector<Order> &orders);

void handleEditOrder(const string &id, vector<Order> &orders);

void handleDeleteOrder(const string &id, vector<Order> &orders);