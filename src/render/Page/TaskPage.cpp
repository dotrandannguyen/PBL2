
#include "TaskPage.h"

void renderTaskPage(SDL_Renderer *renderer, TTF_Font *font, int startX)
{
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color headerColor = {200, 200, 200, 255};

    int menuHeight = 70;
    int y = menuHeight;
    int rowHeight = 40;
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    vector<string> headers = {"TaskID", "DroneID", "OrderID", "Algorithim", "PathLength", "Duration", "Status", "Active"};

    vector<int> colWidths = {120, 120, 120, 150, 150, 120, 120, 120};

    int totalWidth = 0;
    for (auto w : colWidths)
    {
        totalWidth += w;
    }

    float scale = (float)(winW - startX) / totalWidth;

    for (auto w : colWidths)
    {
        w = static_cast<int>(w * scale);
    }

    int x = startX;

    for (size_t i = 0; i < headers.size(); i++)
    {
        SDL_Rect headerRect = {x, y, colWidths[i], rowHeight};
        SDL_SetRenderDrawColor(renderer, headerColor.r, headerColor.g, headerColor.b, headerColor.a);
        SDL_RenderFillRect(renderer, &headerRect);
        int textW, textH;
        TTF_SizeText(font, headers[i].c_str(), &textW, &textH);
        int textX = x + (colWidths[i] - textW) / 2;
        int textY = y + (rowHeight - textH) / 2;
        renderText(renderer, font, headers[i], textX, textY, textColor);
        x += colWidths[i];
    }

    y += rowHeight;
}