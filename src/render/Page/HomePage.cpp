#include "HomePage.h"

SDL_Point getDronePosXY(const string &pos)
{
    if (pos.size() < 2)
        return {0, 0};

    char zone = pos[0];
    int index = pos[1] - '0';

    int baseX = 100 * (zone - 'A' + 1);
    int baseY = 100 * index;

    return {baseX + 100, baseY + 100};
}

void renderHomePage(SDL_Renderer *renderer, TTF_Font *fontSmall, const std::vector<Drone> &drones)
{
    SDL_Color textColor = {0, 0, 0, 255};

    // Vẽ từng drone
    for (auto &d : drones)
    {
        SDL_Rect droneRect = {static_cast<int>(d.getX()), static_cast<int>(d.getY()), 20, 20};

        if (d.getStatus() == "idle")
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
        else if (d.getStatus() == "busy")
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);

        SDL_RenderFillRect(renderer, &droneRect);

        // Hiển thị DroneID bên cạnh
        renderText(renderer, fontSmall, d.getDroneID(),
                   static_cast<int>(d.getX()) - 5,
                   static_cast<int>(d.getY()) - 20,
                   textColor);
    }

    // Lấy kích thước cửa sổ
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    // Vẽ nút Add Drone ở góc phải bên dưới
    int btnW = 120, btnH = 40;
    SDL_Rect addBtn = {w - btnW - 20, h - btnH - 20, btnW, btnH}; // cách viền 20 px
    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
    SDL_RenderFillRect(renderer, &addBtn);
    renderText(renderer, fontSmall, "Add Drone", addBtn.x + 10, addBtn.y + 10, {255, 255, 255, 255});
}

// Xử lý click nút Add Drone

void handleHomePageClick(SDL_Renderer *renderer, int mx, int my, vector<Drone> &drones)
{
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h); // lấy đúng renderer
    int btnW = 120, btnH = 40;
    SDL_Rect addBtn = {w - btnW - 20, h - btnH - 20, btnW, btnH};
    if (isMouseInside(addBtn, mx, my))
    {
        isAddingDrone = true;
    }
}

// Xử lý click chọn vị trí drone mới
void handleAddDroneClick(int mx, int my, vector<Drone> &drones)
{
    if (!isAddingDrone)
        return;

    int idNum = drones.size() + 1;
    string newID = "D00" + to_string(idNum);
    string name = "Drone_" + to_string(idNum);

    // Tạo drone mới trực tiếp với tọa độ click
    Drone newDrone(newID, name, static_cast<float>(mx), static_cast<float>(my), 40.0f, 100, "idle");
    drones.push_back(newDrone);

    writeDronesToFile("D:/Drone-project/src/data/Drone.txt", drones);

    isAddingDrone = false;
}