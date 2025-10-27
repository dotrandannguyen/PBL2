#include "TaskPage.h"

vector<TaskButton> taskButtons;

void renderTaskPage(SDL_Renderer *renderer, TTF_Font *font, const vector<Task> &tasks, int startX)
{
    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Color headerColor = {200, 200, 200, 255};
    SDL_Color btnColor = {23, 162, 184, 255};
    SDL_Color btnTextColor = {255, 255, 255, 255};

    int menuHeight = 70;
    int y = menuHeight;
    int rowHeight = 40;
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);

    // Nút Add Task
    int btnAddW = 140;
    int btnAddH = 40;
    SDL_Rect addBtn = {winW - btnAddW - 30, 15, btnAddW, btnAddH};
    SDL_Color addBtnColor = {40, 167, 69, 255};
    SDL_Color addBtnText = {255, 255, 255, 255};
    SDL_SetRenderDrawColor(renderer, addBtnColor.r, addBtnColor.g, addBtnColor.b, 255);
    SDL_RenderFillRect(renderer, &addBtn);
    int textW, textH;
    TTF_SizeText(font, "+ Add Task", &textW, &textH);
    renderText(renderer, font, "+ Add Task",
               addBtn.x + (btnAddW - textW) / 2,
               addBtn.y + (btnAddH - textH) / 2,
               addBtnText);

    // Header
    vector<string> headers = {"TaskID", "DroneID", "OrderID", "Algorithm", "PathLength", "Duration", "Status", "Action"};
    vector<int> colWidths = {100, 100, 100, 150, 150, 120, 120, 120};

    int totalWidth = 0;
    for (auto w : colWidths)
        totalWidth += w;
    float scale = (float)(winW - startX - 20) / totalWidth;

    for (auto &w : colWidths)
        w = static_cast<int>(w * scale);

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
    taskButtons.clear();

    // Vẽ từng Task
    for (auto &t : tasks)
    {
        x = startX;
        vector<string> row = {
            t.getTaskID(),
            t.getDroneID(),
            t.getOrderID(),
            t.getAlgorithmUsed(),
            to_string(t.getPathLength()),
            to_string(t.getDuration()),
            t.getStatus()};

        for (size_t i = 0; i < row.size(); i++)
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

        // Nút Active
        int btnWidth = 80, btnHeight = 30;
        SDL_Rect activeBtn = {x + (colWidths.back() - btnWidth) / 2, y + (rowHeight - btnHeight) / 2, btnWidth, btnHeight};

        SDL_SetRenderDrawColor(renderer, btnColor.r, btnColor.g, btnColor.b, 255);
        SDL_RenderFillRect(renderer, &activeBtn);

        int textW2, textH2;
        TTF_SizeText(font, "Activate", &textW2, &textH2);
        renderText(renderer, font, "Activate",
                   activeBtn.x + (btnWidth - textW2) / 2,
                   activeBtn.y + (btnHeight - textH2) / 2,
                   btnTextColor);

        taskButtons.push_back({activeBtn, t.getTaskID()});

        y += rowHeight;
    }
}

void handleAddTask(vector<Task> &tasks, vector<Drone> &drones, vector<Order> &orders)
{
    if (drones.empty() || orders.empty())
    {
        cout << "Khong the tao Task  Drone hoac Order rong!\n";
        return;
    }

    string algo;
    cout << "Nhap thuat toan su dung (AStar/Dijkstra): ";
    cin >> algo;

    Drone *d = &drones.front();
    Order *o = &orders.front();

    Task newTask("T" + to_string(tasks.size() + 1),
                 d,
                 o,
                 algo,
                 100.0, // tạm giá trị
                 15.0,
                 "assigned");

    tasks.push_back(newTask);
    writeTasksToFile("D:/Drone-project/src/data/Tasks.txt", tasks);
    cout << "Task moi da duoc them.\n";
}
