#ifndef TASKPAGE_H
#define TASKPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../../core/Drone.h"
#include "../../core/Task.h"
#include "../Renderer.h"

struct TaskButton
{
    SDL_Rect activateBtn;
    string taskID;
};

extern vector<TaskButton> taskButtons;

void renderTaskPage(SDL_Renderer *renderer, TTF_Font *font, const vector<Task> &tasks, int startX);
void handleAddTask(vector<Task> &tasks, vector<Drone> &drones, vector<Order> &orders);

#endif