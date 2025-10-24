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
extern vector<Drone> drones; // hoặc truyền vào tham số nếu bạn dùng scope khác
extern vector<Node> nodes;
extern vector<Edge> edges;

void renderOrderPage(SDL_Renderer *renderer, TTF_Font *font, const std::vector<Order> &orders, int startX);

void handleAddOrder(vector<Order> &orders);