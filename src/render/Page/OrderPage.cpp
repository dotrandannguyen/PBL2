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

    // add button
    int btnAddW = 140;
    int btnAddH = 40;
    SDL_Rect addBtn = {winW - btnAddW - 30, 15, btnAddW, btnAddH};
    SDL_Color addBtnColor = {40, 167, 69, 255};
    SDL_Color addBtnText = {255, 255, 255, 255};
    SDL_SetRenderDrawColor(renderer, addBtnColor.r, addBtnColor.g, addBtnColor.b, 255);
    SDL_RenderFillRect(renderer, &addBtn);
    int textW, textH;
    TTF_SizeText(font, "+ Add Order", &textW, &textH);
    renderText(renderer, font, "+ Add Order",
               addBtn.x + (btnAddW - textW) / 2,
               addBtn.y + (btnAddH - textH) / 2,
               addBtnText);

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

    // ve lai order button
    orderButtons.clear();

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

        orderButtons.push_back({editBtn, delBtn, o.getOrderID()});

        y += rowHeight;
    }
}

void handleAddOrder(vector<Order> &orders)
{
    string pickup, dropoff;
    cout << "Pickup: ";
    cin >> pickup;
    cout << "Dropoff: ";
    cin >> dropoff;
    Order newOrder(
        "O" + to_string(orders.size() + 1), // ID tự tăng
        pickup,
        dropoff,
        1.0,      // weight mặc định
        "high",   // priority mặc định
        "pending" // status mặc định
    );
    orders.push_back(newOrder);

    writeOrdersToFile("D:/Drone-project/src/data/Orders.txt", newOrder);
    // cout << "[DEBUG AFTER ADD] orders.size() = " << orders.size() << endl;
    // for (auto &o : orders)
    //     cout << o.getOrderID() << " " << o.getStatus() << endl;
}

void handleEditOrder(const string &id, vector<Order> &orders)
{
    for (auto &o : orders)
    {
        if (o.getOrderID() == id)
        {
            string newPickUp, newDropOff;
            float newWeight;
            string newPriority;
            cout << "EDIT ORDER: " << id << endl;
            cout << "New PickUp: ";
            cin >> newPickUp;
            cout << "New DropOff: ";
            cin >> newDropOff;
            cout << "New Weight: ";
            cin >> newWeight;
            cout << "New Priority: ";
            cin >> newPriority;
            o.setPickupLocation(newPickUp);
            o.setDropoffLocation(newDropOff);
            o.setWeight(newWeight);
            o.setPriority(newPriority);
            overWriteOrdersToFile("D:/Drone-project/src/data/Orders.txt", orders);
            break;
        }
    }
}

void handleDeleteOrder(const string &id, vector<Order> &orders)
{
    for (int i = 0; i < orders.size(); i++)
    {
        if (orders[i].getOrderID() == id)
        {
            orders.erase(orders.begin() + i);
            cout << "Deleted Order" << id << endl;
            overWriteOrdersToFile("D:/Drone-project/src/data/Orders.txt", orders);
            break;
        }
    }
}
