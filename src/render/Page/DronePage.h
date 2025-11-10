#ifndef DRONEPAGE_H
#define DRONEPAGE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>
#include <iomanip>
#include <iostream>
#include "../../core/Drone.h"
#include "../../core/Node.h"
#include "../Renderer.h"

struct DroneButton
{
    SDL_Rect editBtn;
    SDL_Rect delBtn;
    string droneID;
};
extern vector<DroneButton> droneButtons;

struct PageButtons
{
    SDL_Rect prevBtn;
    SDL_Rect nextBtn;
};
extern PageButtons pageButtons;
extern int currentDronePage;

const int DRONES_PER_PAGE = 15;

// nut delete edit

void renderDronePage(SDL_Renderer *renderer, TTF_Font *font, const std::vector<Drone> &drones, int startX);

void handleAddDrone(SDL_Renderer *renderer, int mx, int my, vector<Drone> &drones, const vector<Node> &nodes);

void handleEditDrone(const string &id, vector<Drone> &drones);

void handleDeleteDrone(const string &id, vector<Drone> &drones);

#endif
