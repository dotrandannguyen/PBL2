#include "TaskPage.h"

PageTaskButton pageTaskButtons;
int currentTaskPage = 0;

void renderTaskPage(SDL_Renderer *renderer, TTF_Font *font, const vector<Task> tasks, int startX)
{
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color headerColor = {200, 200, 200, 255}; // r g b a

    int menuHeight = 70; // khoang trong cho nut menu
    int y = menuHeight;  // bat dau ve duoi menu
    int rowHeight = 40;  // kc giua cac cot

    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);
    int textW, textH;
    TTF_SizeText(font, "+ Add Order", &textW, &textH);
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

    int totalTasks = tasks.size();
    int totalPages = (totalTasks + TASKS_PER_PAGE - 1) / TASKS_PER_PAGE;
    int startIndex = currentTaskPage * TASKS_PER_PAGE;
    int endIndex = min(startIndex + TASKS_PER_PAGE, totalTasks);

    for (int i = startIndex; i < endIndex; i++)
    {
        const Task &t = tasks[i];
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
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
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

    int btnW = 100, btnH = 35;
    int spacing = 20;

    int groupWidth = btnW * 2 + spacing * 2 + 150;
    int centerX = winW - groupWidth / 2 - 250;
    int baseY = y + 20;

    // Prev
    SDL_Rect prevBtn = {centerX, baseY, btnW, btnH};

    // Page Box
    string pageText = "Page " + to_string(currentTaskPage + 1) + " / " + to_string(totalPages);
    TTF_SizeText(font, pageText.c_str(), &textW, &textH);

    int boxW = textW + 40;
    int boxH = btnH;
    SDL_Rect pageBox = {prevBtn.x + btnW + spacing, baseY, boxW, boxH};
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
    SDL_RenderFillRect(renderer, &pageBox);
    SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255);
    SDL_RenderDrawRect(renderer, &pageBox);

    // text Page
    renderText(renderer, font, pageText,
               pageBox.x + (pageBox.w - textW) / 2,
               pageBox.y + (pageBox.h - textH) / 2,
               {0, 0, 0, 255});
    // Next
    SDL_Rect nextBtn = {pageBox.x + boxW + spacing, baseY, btnW, btnH};

    // ve nut
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderFillRect(renderer, &prevBtn);
    SDL_RenderFillRect(renderer, &nextBtn);

    // Text Prev/Next
    TTF_SizeText(font, "Prev", &textW, &textH);
    renderText(renderer, font, "Prev", prevBtn.x + (btnW - textW) / 2,
               prevBtn.y + (btnH - textH) / 2,
               {255, 255, 255, 255});

    TTF_SizeText(font, "Next", &textW, &textH);
    renderText(renderer, font, "Next",
               nextBtn.x + (btnW - textW) / 2,
               nextBtn.y + (btnH - textH) / 2,
               {255, 255, 255, 255});

    pageTaskButtons = {prevBtn, nextBtn};
}