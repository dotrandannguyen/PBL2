#include "DronePage.h"
#include "D:/Drone-project/src/render/Renderer.h"
#include <iomanip>
#include <sstream>

using namespace std;

struct DroneButton
{
    SDL_Rect rect;
    string label;
};

void renderDronePage(SDL_Renderer *renderer, TTF_Font *font, const vector<Drone> &drones, int startX)
{
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color headerColor = {200, 200, 200, 255};
    SDL_Color btnColor = {23, 162, 184, 255};
    SDL_Color btnTextColor = {255, 255, 255, 255};

    int menuHeight = 70; // khoảng trống cho nút menu
    int y = menuHeight;  // bắt đầu vẽ dưới menu
    int rowHeight = 40;

    // Lấy kích thước cửa sổ
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    // 1️⃣ Header
    vector<string> headers = {"DroneID", "Name", "Position", "Speed", "Battery", "Status", "Actions"};
    vector<int> colWidths = {
        100, 120, 200, 120, 90, 100, 200 // 7 cột
    };

    // Nếu muốn bảng rộng toàn màn hình, scale colWidths theo window
    int totalWidth = 0;
    for (auto w : colWidths)
        totalWidth += w;

    float scale = (float)(winW - startX - 20) / totalWidth; // 20 px margin phải
    for (auto &w : colWidths)
        w = static_cast<int>(w * scale);

    int x = startX;

    for (size_t i = 0; i < headers.size(); ++i)
    {
        SDL_Rect headerRect = {x, y, colWidths[i], rowHeight};
        SDL_SetRenderDrawColor(renderer, headerColor.r, headerColor.g, headerColor.b, headerColor.a);
        SDL_RenderFillRect(renderer, &headerRect);
        renderText(renderer, font, headers[i], x + 5, y + 10, textColor);
        x += colWidths[i];
    }

    y += rowHeight; // sang dòng dữ liệu

    // 2️⃣ Vẽ dữ liệu drone
    for (auto &d : drones)
    {
        x = startX;

        ostringstream posStream;
        posStream << fixed << setprecision(1) << "(" << d.getX() << ", " << d.getY() << ")";

        vector<string> row = {
            d.getDroneID(),
            d.getName(),
            posStream.str(),
            to_string(d.getSpeed()),
            to_string(d.getBattery()) + "%",
            d.getStatus()};

        for (size_t i = 0; i < row.size(); ++i)
        {
            SDL_Rect cell = {x, y, colWidths[i], rowHeight};
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
            SDL_RenderFillRect(renderer, &cell);
            renderText(renderer, font, row[i], x + 5, y + 10, textColor);
            x += colWidths[i];
        }

        // Nút Edit / Delete
        SDL_Rect editBtn = {x, y + 5, 70, 30};
        SDL_Rect delBtn = {x + 80, y + 5, 70, 30};

        SDL_SetRenderDrawColor(renderer, btnColor.r, btnColor.g, btnColor.b, 255);
        SDL_RenderFillRect(renderer, &editBtn);
        SDL_RenderFillRect(renderer, &delBtn);

        renderText(renderer, font, "Edit", editBtn.x + 10, editBtn.y + 5, btnTextColor);
        renderText(renderer, font, "Delete", delBtn.x + 5, delBtn.y + 5, btnTextColor);

        y += rowHeight;
    }
}
