#include "OrderPage.h"

using namespace std;

void renderOrderPage(SDL_Renderer *renderer, TTF_Font *font, const vector<Order> &orders, int startX)
{
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color headerColor = {200, 200, 200, 255}; // r g b a
    SDL_Color btnColor = {23, 162, 184, 255};
    SDL_Color btnTextColor = {255, 255, 255, 255};

    int menuHeight = 70; // khoang trong cho nut menu
    int y = menuHeight;  // bat dau ve duoi menu
    int rowHeight = 40;  // kc giua cac cot

    // kich thuoc window
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    vector<string> headers = {"OrderID", "Pickup", "Dropoff", "Weight", "Priority", "Status", "Actions"};

    vector<int> colWidths = {120, 120, 120, 200, 120, 120, 200};

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

    for (auto &o : orders)
    {
        x = startX;

        vector<string> row = {
            o.getOrderID(),
            o.getPickupLocation(),
            o.getDropoffLocation(),
            to_string(o.getWeight()),
            o.getPriority(),
            o.getStatus(),
        };

        for (size_t i = 0; i < row.size(); i++)
        {
            SDL_Rect cell = {x,
                             y,
                             colWidths[i],
                             rowHeight};
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
            SDL_RenderFillRect(renderer, &cell);
            int textW, textH;
            TTF_SizeText(font, row[i].c_str(), &textW, &textH);
            int textX = x + (colWidths[i] - textW) / 2;
            int textY = y + (rowHeight - textH) / 2;
            renderText(renderer, font, row[i], textX, textY, textColor);
            x += colWidths[i];
        }

        int btnWidth = 70;
        int btnHeight = 30;
        int btnGap = 20; // khoảng cách giữa 2 nút

        int totalBtnWidth = btnWidth * 2 + btnGap;

        // Căn giữa các nút trong vùng còn lại của bảng
        int btnStartX = x + (colWidths.back() - totalBtnWidth) / 2;
        int btnY = y + (rowHeight - btnHeight) / 2;

        // Vẽ nút
        SDL_Rect editBtn = {btnStartX, btnY, btnWidth, btnHeight};
        SDL_Rect delBtn = {btnStartX + btnWidth + btnGap, btnY, btnWidth, btnHeight};

        // Vẽ màu nút
        SDL_SetRenderDrawColor(renderer, btnColor.r, btnColor.g, btnColor.b, 255);
        SDL_RenderFillRect(renderer, &editBtn);
        SDL_RenderFillRect(renderer, &delBtn);

        // Căn giữa chữ trong nút
        int textW, textH;

        //  EDIT
        TTF_SizeText(font, "Edit", &textW, &textH);
        renderText(renderer, font, "Edit",
                   editBtn.x + (btnWidth - textW) / 2,
                   editBtn.y + (btnHeight - textH) / 2,
                   btnTextColor);

        // DELETE
        TTF_SizeText(font, "Delete", &textW, &textH);
        renderText(renderer, font, "Delete",
                   delBtn.x + (btnWidth - textW) / 2,
                   delBtn.y + (btnHeight - textH) / 2,
                   btnTextColor);

        y += rowHeight;
    }
}