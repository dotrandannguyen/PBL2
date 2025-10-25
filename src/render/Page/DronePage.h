#ifndef DRONEPAGE_H
#define DRONEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../../core/Drone.h"
#include "../Renderer.h"

struct DroneButton
{
    SDL_Rect editBtn;
    SDL_Rect delBtn;
    string droneID;
};

// nut delete edit
extern vector<DroneButton> droneButtons;

void renderDronePage(SDL_Renderer *renderer, TTF_Font *font, const std::vector<Drone> &drones, int startX);

void handleEditDrone(const string &id, vector<Drone> &drones);

void handleDeleteDrone(const string &id, vector<Drone> &drones);

#endif
