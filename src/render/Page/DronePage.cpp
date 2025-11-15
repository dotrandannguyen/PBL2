#include "DronePage.h"

using namespace std;

PageButtons pageButtons;  // biến toàn cục
int currentDronePage = 0; // trang đầu tiên

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

    // add button
    int btnAddW = 140;
    int btnAddH = 40;
    SDL_Rect addBtn = {winW - btnAddW - 30, 15, btnAddW, btnAddH};
    SDL_Color addBtnColor = {40, 167, 69, 255};
    SDL_Color addBtnText = {255, 255, 255, 255};
    SDL_SetRenderDrawColor(renderer, addBtnColor.r, addBtnColor.g, addBtnColor.b, 255);
    SDL_RenderFillRect(renderer, &addBtn);
    int textW, textH;
    TTF_SizeText(font, "+ Add Drone", &textW, &textH);
    renderText(renderer, font, "+ Add Drone",
               addBtn.x + (btnAddW - textW) / 2,
               addBtn.y + (btnAddH - textH) / 2,
               addBtnText);

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

    // PHÂN TRANG
    droneButtons.clear();
    int totalDrones = drones.size();
    int totalPages = (totalDrones + DRONES_PER_PAGE - 1) / DRONES_PER_PAGE;

    int startIndex = currentDronePage * DRONES_PER_PAGE;
    int endIndex = min(startIndex + DRONES_PER_PAGE, totalDrones);

    // Vẽ dữ liệu cho trang hiện tại
    for (int i = startIndex; i < endIndex; ++i)
    {
        const Drone &d = drones[i];
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

        for (size_t j = 0; j < row.size(); ++j)
        {
            SDL_Rect cell = {x, y, colWidths[j], rowHeight};
            SDL_SetRenderDrawColor(renderer, 245, 245, 245, 255);
            SDL_RenderFillRect(renderer, &cell);
            int textW, textH;
            TTF_SizeText(font, row[j].c_str(), &textW, &textH);
            int textX = x + (colWidths[j] - textW) / 2;
            int textY = y + (rowHeight - textH) / 2;
            renderText(renderer, font, row[j], textX, textY, textColor);
            x += colWidths[j];
        }

        if (drones.size() != 0)
        {
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

        // Delete
        TTF_SizeText(font, "Delete", &textW, &textH);
        renderText(renderer, font, "Delete",
                   delBtn.x + (btnW - textW) / 2,
                   delBtn.y + (btnH - textH) / 2,
                   btnTextColor);

        droneButtons.push_back({editBtn, delBtn, d.getDroneID()});

        y += rowHeight;
    }

    if (drones.size() != 0)
    {
        int btnW = 100, btnH = 35;
        int spacing = 20; // khoảng cách giữa Prev, PageBox, Next

        // Tính vị trí trung tâm cụm 3 nút
        int groupWidth = btnW * 2 + spacing * 2 + 150; // ước lượng thêm chỗ cho khung trang
        int centerX = winW - groupWidth / 2 - 250;     // căn giữa gần mép phải (tùy chỉnh nếu cần)
        int baseY = y + 20;

        // Prev
        SDL_Rect prevBtn = {centerX, baseY, btnW, btnH};

        // Page Box
        string pageText = "Page " + to_string(currentDronePage + 1) + " / " + to_string(totalPages);

        TTF_SizeText(font, pageText.c_str(), &textW, &textH);

        int boxW = textW + 50;
        int boxH = btnH;
        SDL_Rect pageBox = {prevBtn.x + btnW + spacing, baseY, boxW, boxH};

        SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255); // xanh nhạt
        SDL_RenderFillRect(renderer, &pageBox);
        SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // viền xanh đậm
        SDL_RenderDrawRect(renderer, &pageBox);

        int textX = pageBox.x + (pageBox.w - textW) / 2;
        int textY = pageBox.y + (pageBox.h - textH) / 2;

        renderText(renderer, font, pageText, textX, textY, {0, 0, 0, 255});
        // Next
        SDL_Rect nextBtn = {pageBox.x + boxW + spacing, baseY, btnW, btnH};

        //  Vẽ nút
        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
        SDL_RenderFillRect(renderer, &prevBtn);
        SDL_RenderFillRect(renderer, &nextBtn);

        //  Text Prev/Next
        TTF_SizeText(font, "Prev", &textW, &textH);
        renderText(renderer, font, "Prev",
                   prevBtn.x + (btnW - textW) / 2,
                   prevBtn.y + (btnH - textH) / 2,
                   {255, 255, 255, 255});

        TTF_SizeText(font, "Next", &textW, &textH);
        renderText(renderer, font, "Next",
                   nextBtn.x + (btnW - textW) / 2,
                   nextBtn.y + (btnH - textH) / 2,
                   {255, 255, 255, 255});
        // Lưu vị trí
        pageButtons = {prevBtn, nextBtn};
    }
}

void handleAddDrone(SDL_Renderer *renderer, int mx, int my, vector<Drone> &drones, const vector<Node> &nodes)
{
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    int idNum = drones.size() + 1;
    string newID = "D00" + to_string(idNum);
    string name = "Drone_" + to_string(idNum);

    int btnAddW = 140;
    int btnAddH = 40;
    SDL_Rect addBtn = {w - btnAddW - 30, 15, btnAddW, btnAddH};
    // Mặc định spawn ở node 1 hoặc node 2
    if (isMouseInside(addBtn, mx, my))
    {
        string startNodeID;
        if (idNum % 2 == 1)
            startNodeID = "N01";
        else
            startNodeID = "N02";

        // Tìm tọa độ node tương ứng
        float x = 0, y = 0;
        for (auto &n : nodes)
        {
            if (n.getNodeID() == startNodeID)
            {
                x = n.getX();
                y = n.getY();
                break;
            }
        }
        Drone newDrone(newID, name, x, y, 100.0f, 100, "idle", startNodeID);

        drones.push_back(newDrone);
        writeDronesToFile("D:/Drone-project/src/data/Drone.txt", drones);
    }
}

void handleEditDrone(const string &id, vector<Drone> &drones)
{
    for (auto &d : drones)
    {
        if (d.getDroneID() == id)
        {
            string newName;
            float newSpeed;
            int newBattery;
            cout << "EDIT DRONE: " << id << endl;
            cout << "New Name: ";
            cin >> newName;
            cout << "New Speed: ";
            cin >> newSpeed;
            cout << "New Battery: ";
            cin >> newBattery;
            d.setName(newName);
            d.setSpeed(newSpeed);
            d.setBattery(newBattery);
            writeDronesToFile("D:/Drone-project/src/data/Drone.txt", drones);
            break;
        }
    }
}

void handleDeleteDrone(const string &id, vector<Drone> &drones)
{
    for (int i = 0; i < drones.size(); i++)
    {
        if (drones[i].getDroneID() == id)
        {
            drones.erase(drones.begin() + i);
            cout << "Deleted Drone" << id << endl;
            writeDronesToFile("D:/Drone-project/src/data/Drone.txt", drones);
            break;
        }
    }
}
