#include "TaskPage.h"

void renderTaskPage(SDL_Renderer *renderer, TTF_Font *font, const vector<Task> tasks, int startX)
{
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color headerColor = {200, 200, 200, 255}; // r g b a
    SDL_Color rowColor = {240, 240, 240, 255};
    SDL_Color btnColor = {23, 162, 184, 255};
    SDL_Color btnTextColor = {255, 255, 255, 255};

    int menuHeight = 70; // khoang trong cho nut menu
    int y = menuHeight;  // bat dau ve duoi menu
    int rowHeight = 40;  // kc giua cac cot

    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    vector<string> headers = {"TaskID", "DroneID", "OrderID", "AlgorithmUsed", "PathLength", "Duration", "Status"};
    vector<int> colWidths = {120, 120, 120, 200, 200, 200, 200};

    int totalWidth = 0;
    for (auto w : colWidths)
    {
        totalWidth += w;
    }
    float scale = (float)(winW - startX - 20) / totalWidth; // margin right 20px

    for (auto &w : colWidths)
    {
        w = static_cast<int>(w * scale);
    }

    int x = startX;

    for (size_t i = 0; i < headers.size(); i++)
    {
        SDL_Rect headerReact = {x, y, colWidths[i], rowHeight};
        SDL_SetRenderDrawColor(renderer, headerColor.r, headerColor.g, headerColor.b, headerColor.a);
        SDL_RenderFillRect(renderer, &headerReact);
        int textW, textH;
        TTF_SizeText(font, headers[i].c_str(), &textW, &textH);
        int textX = x + (colWidths[i] - textW) / 2;
        int textY = y + (rowHeight - textH) / 2;
        renderText(renderer, font, headers[i], textX, textY, textColor);
        x += colWidths[i];
    }

    y += rowHeight; // xuong dong
                    // Vẽ từng task
    for (const auto &t : tasks)
    {
        x = startX;

        vector<string> row = {
            t.getTaskID(),
            t.getDrone() ? t.getDrone()->getDroneID() : "",
            t.getOrder() ? t.getOrder()->getOrderID() : "",
            t.getAlgorithmUsed(),
            to_string(t.getPathLength()),
            to_string(t.getDuration()),
            t.getStatus()};

        for (size_t i = 0; i < row.size(); i++)
        {
            SDL_Rect cellRect = {x, y, colWidths[i], rowHeight};
            SDL_SetRenderDrawColor(renderer, rowColor.r, rowColor.g, rowColor.b, rowColor.a);
            SDL_RenderFillRect(renderer, &cellRect);

            int textW, textH;
            TTF_SizeText(font, row[i].c_str(), &textW, &textH);
            int textX = x + (colWidths[i] - textW) / 2;
            int textY = y + (rowHeight - textH) / 2;
            renderText(renderer, font, row[i], textX, textY, textColor);

            x += colWidths[i];
        }

        y += rowHeight; // xuống dòng tiếp theo
    }
}