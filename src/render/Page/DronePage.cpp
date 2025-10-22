#include "DronePage.h"

using namespace std;

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

    //  Header
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
        int textW, textH;
        TTF_SizeText(font, headers[i].c_str(), &textW, &textH);
        int textX = x + (colWidths[i] - textW) / 2;
        int textY = y + (rowHeight - textH) / 2;
        renderText(renderer, font, headers[i], textX, textY, textColor);
        x += colWidths[i];
    }

    y += rowHeight; // sang dòng dữ liệu

    //  Vẽ dữ liệu drone
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
            int textW, textH;
            TTF_SizeText(font, row[i].c_str(), &textW, &textH);
            int textX = x + (colWidths[i] - textW) / 2;
            int textY = y + (rowHeight - textH) / 2;
            renderText(renderer, font, row[i], textX, textY, textColor);
            x += colWidths[i];
        }

        int btnW = 70;
        int btnH = 30;
        int btnGap = 20;

        int totalBtnWidth = btnW * 2 + btnGap;

        int btnStartX = x + (colWidths.back() - totalBtnWidth) / 2;
        int btnY = y + (rowHeight - btnH) / 2;

        SDL_Rect editBtn = {btnStartX, btnY, btnW, btnH};
        SDL_Rect delBtn = {btnStartX + btnW + btnGap, btnY, btnW, btnH};

        SDL_SetRenderDrawColor(renderer, btnColor.r, btnColor.g, btnColor.b, 255);
        SDL_RenderFillRect(renderer, &editBtn);
        SDL_RenderFillRect(renderer, &delBtn);

        int textW, textH;

        // Edit
        TTF_SizeText(font, "Edit", &textW, &textH);
        renderText(renderer, font, "Edit",
                   editBtn.x + (btnW - textW) / 2,
                   editBtn.y + (btnH - textH) / 2,
                   btnTextColor);

        // DELETE
        TTF_SizeText(font, "Delete", &textW, &textH);
        renderText(renderer, font, "Delete",
                   delBtn.x + (btnW - textW) / 2,
                   delBtn.y + (btnH - textH) / 2,
                   btnTextColor);

        y += rowHeight;
    }
}
