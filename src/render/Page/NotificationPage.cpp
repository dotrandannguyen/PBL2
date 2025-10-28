#include "NotificationPage.h"

void renderNotificationPage(SDL_Renderer *renderer, TTF_Font *font, const vector<string> &notifications)
{
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    // Bắt đầu vẽ từ vị trí lệch sang phải để không bị sidebar đè lên
    int contentX = static_cast<int>(winW * 0.15) + 40; // sidebar chiếm 15%, chừa thêm 40px
    int y = 100;

    // Khung nền nhẹ cho vùng thông báo
    SDL_Rect bgRect = {contentX - 20, 60, winW - contentX - 40, winH - 120};
    SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255); // nền sáng
    SDL_RenderFillRect(renderer, &bgRect);

    // Tiêu đề
    SDL_Color titleColor = {23, 42, 69, 255}; // xanh đậm đồng bộ sidebar
    renderText(renderer, font, "Notification Center", contentX, 70, titleColor);

    // Màu cho từng loại thông báo
    SDL_Color systemColor = {255, 100, 50, 255}; // cam đỏ cho hệ thống
    SDL_Color debugColor = {66, 135, 245, 255};  // xanh dương cho debug
    SDL_Color normalColor = {60, 60, 60, 255};   // xám đậm cho thông thường

    for (const auto &msg : notifications)
    {
        SDL_Color color;
        if (msg.find("[SYSTEM]") != string::npos)
            color = systemColor;
        else if (msg.find("[DEBUG]") != string::npos)
            color = debugColor;
        else
            color = normalColor;

        renderText(renderer, font, msg.c_str(), contentX, y, color);
        y += 30;
    }

    if (notifications.empty())
    {
        renderText(renderer, font, "No notifications yet.", contentX, y, {128, 128, 128, 255});
    }
}
