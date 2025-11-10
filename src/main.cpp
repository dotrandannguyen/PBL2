#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "render/Renderer.h"
#include "core/Drone.h"
#include "core/Order.h"
#include "render/Page/OrderPage.h"
#include "render/Page/TaskPage.h"
#include "render/Page/HomePage.h"
#include "render/Page/DronePage.h"
#include "render/Page/NotificationPage.h"
#include "algorithm/PathFinder/Dijkstra.h"
#include "algorithm/Assignment/Greedy.h"
#include "utils/notification.h"
using namespace std;

bool isAddingDrone = false;
bool isAddingNode = false;
bool isAddingOrder = false;

vector<Drone> drones = readDronesFromFile("D:/Drone-project/src/data/Drone.txt");
vector<Node> nodes = readNodesFromFile("D:/Drone-project/src/data/Node.txt");
vector<Edge> edges = readEdgesFromFile("D:/Drone-project/src/data/Edge.txt");
vector<Order> orders = readOrdersFromFile("D:/Drone-project/src/data/Orders.txt");
vector<Task> tasks = readTasksFromFile("D:/Drone-project/src/data/Task.txt");

struct Button
{
    SDL_Rect rect;
    string label;
    bool selected;
};

vector<DroneButton> droneButtons;
vector<OrderButton> orderButtons;
vector<string> notifications;
vector<NoFlyZone> noFlyZones;

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! " << SDL_GetError() << "\n";
        return 1;
    }

    if (TTF_Init() == -1)
    {
        cout << "TTF could not initialize! " << TTF_GetError() << "\n";
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        cout << "IMG could not initialize! " << IMG_GetError() << "\n";
        return 1;
    }

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int screenWidth = DM.w;
    int screenHeight = DM.h;

    SDL_Window *window = SDL_CreateWindow("Dashboard - SDL2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          screenWidth,
                                          screenHeight,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color bgColor = {245, 247, 250, 255};
    SDL_Color sidebarColor = {23, 42, 69, 255};
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color selectedColor = {255, 174, 66, 255};

    // font
    TTF_Font *font = TTF_OpenFont("C:/Windows/Fonts/segoeui.ttf", 22);
    TTF_Font *fontSmall = TTF_OpenFont("C:/Windows/Fonts/segoeui.ttf", 12);

    // texture
    SDL_Texture *homeIcon = loadTexture(renderer, "D:/Drone-project/src/assets/home.png");
    SDL_Texture *droneIcon = loadTexture(renderer, "D:/Drone-project/src/assets/drone.png");
    SDL_Texture *orderIcon = loadTexture(renderer, "D:/Drone-project/src/assets/order.png");
    SDL_Texture *taskIcon = loadTexture(renderer, "D:/Drone-project/src/assets/task.png");
    SDL_Texture *notificationIcon = loadTexture(renderer, "D:/Drone-project/src/assets/notification.png");
    SDL_Texture *graphIcon = loadTexture(renderer, "D:/Drone-project/src/assets/graph.png");

    if (!font)
    {
        cout << "Không tìm thấy font!\n";
        return 1;
    }

    // Sidebar width chiếm 15% màn hình
    int sidebarWidth = static_cast<int>(screenWidth * 0.15);
    int sidebarMargin = 10; // Khoảng cách nút 3 gạch

    // Các nút sidebar tính theo tỷ lệ màn hình
    vector<Button> buttons = {
        {{0, static_cast<int>(screenHeight * 0.15), sidebarWidth, static_cast<int>(screenHeight * 0.06)}, "Home", true},
        {{0, static_cast<int>(screenHeight * 0.23), sidebarWidth, static_cast<int>(screenHeight * 0.06)}, "Drone", false},
        {{0, static_cast<int>(screenHeight * 0.31), sidebarWidth, static_cast<int>(screenHeight * 0.06)}, "Task", false},
        {{0, static_cast<int>(screenHeight * 0.39), sidebarWidth, static_cast<int>(screenHeight * 0.06)}, "Notification", false},
        {{0, static_cast<int>(screenHeight * 0.47), sidebarWidth, static_cast<int>(screenHeight * 0.06)}, "Order", false},
        {{0, static_cast<int>(screenHeight * 0.55), sidebarWidth, static_cast<int>(screenHeight * 0.06)}, "Graph", false}};

    string currentPage = "Home";

    bool quit = false;
    bool sidebarVisible = true;
    bool isMoving = false;
    bool hasStart = false;    // check xem drone đã tab chạy lần nào chưa
    bool hasNewOrder = false; // check xem có đơn hàng mới ko
    auto lastTime = chrono::high_resolution_clock::now();
    SDL_Event e;

    while (!quit)
    {
        int menuX = sidebarVisible ? sidebarWidth + sidebarMargin : sidebarMargin;
        SDL_Rect menuBtn = {menuX, 20, 50, 40};
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mx = e.button.x;
                int my = e.button.y;

                //  Nút 3 gạch — luôn nằm sát mép sidebar

                if (isMouseInside(menuBtn, mx, my))
                {
                    sidebarVisible = !sidebarVisible;
                }

                // Nếu sidebar đang hiển thị, xử lý click các nút
                if (sidebarVisible)
                {
                    for (auto &btn : buttons)
                    {
                        if (isMouseInside(btn.rect, mx, my))
                        {
                            for (auto &b : buttons)
                                b.selected = false;
                            btn.selected = true;
                            currentPage = btn.label;
                        }
                    }
                }
                // Xử lý click trang Home
                if (currentPage == "Home")
                {
                    hanldeHomePageInfoClick(renderer, mx, my);
                    handleHomePageShowEdgeClick(renderer, mx, my);
                    handleHomePageDroneClick(renderer, mx, my, drones, nodes);

                    if (isAddingNode)
                    {
                        handleAddNodeClick(mx, my, nodes, edges);
                    }
                    else
                    {
                        handleHomePageNodeClick(renderer, mx, my);
                    }

                    if (isNoFly)
                    {
                        handleAddNoFlyArea(mx, my);
                    }
                    else
                    {
                        handleHomePageNoFlyClick(renderer, mx, my);
                    }
                }
                else if (currentPage == "Order")
                {
                    int winW, winH;
                    SDL_GetRendererOutputSize(renderer, &winW, &winH);
                    SDL_Rect addBtn = {winW - 140 - 30, 15, 140, 40};
                    if (isMouseInside(addBtn, mx, my))
                    {

                        handleAddOrder(orders);
                        hasNewOrder = true; // cho phep drone chay lai khi co don moi duoc them vao
                    }

                    SDL_Point mousePoint = {mx, my};
                    if (SDL_PointInRect(&mousePoint, &pageOrderButtons.prevBtn))
                    {
                        if (currentOrderPage > 0)
                            currentOrderPage--;
                    }
                    else if (SDL_PointInRect(&mousePoint, &pageOrderButtons.nextBtn))
                    {
                        int totalPage = (orders.size() + ORDERS_PER_PAGE - 1) / ORDERS_PER_PAGE;
                        if (currentOrderPage < totalPage - 1)
                        {
                            currentOrderPage++;
                        }
                    }

                    for (auto &ob : orderButtons)
                    {
                        if (isMouseInside(ob.editBtn, mx, my))
                        {
                            handleEditOrder(ob.OrderID, orders);
                            break;
                        }
                        else if (isMouseInside(ob.delBtn, mx, my))
                        {
                            handleDeleteOrder(ob.OrderID, orders);
                            break;
                        }
                    }
                }
                else if (currentPage == "Drone")
                {
                    handleAddDrone(renderer, mx, my, drones, nodes);
                    SDL_Point mousePoint = {mx, my};
                    if (SDL_PointInRect(&mousePoint, &pageButtons.prevBtn))
                    {
                        if (currentDronePage > 0)
                            currentDronePage--;
                    }
                    else if (SDL_PointInRect(&mousePoint, &pageButtons.nextBtn))
                    {
                        int totalPages = (drones.size() + DRONES_PER_PAGE - 1) / DRONES_PER_PAGE;
                        if (currentDronePage < totalPages - 1)
                            currentDronePage++;
                    }
                    for (auto &db : droneButtons)
                    {

                        if (isMouseInside(db.editBtn, mx, my))
                        {
                            handleEditDrone(db.droneID, drones);
                            break;
                        }
                        else if (isMouseInside(db.delBtn, mx, my))
                        {
                            handleDeleteDrone(db.droneID, drones);
                            break;
                        }
                    }
                }
                else if (currentPage == "Task")
                {
                    int winW, winH;
                    SDL_GetRendererOutputSize(renderer, &winW, &winH);
                    SDL_Rect addBtn = {winW - 140 - 30, 15, 140, 40};
                    if (isMouseInside(addBtn, mx, my))
                    {
                        handleAddTask(tasks, drones, orders);
                    }
                }
            }
            else if (e.key.keysym.sym == SDLK_TAB)
            {
                if (!isMoving)
                {

                    for (auto &d : drones)
                    {

                        snapDroneToNode(d, nodes);
                    }
                    lastTime = chrono::high_resolution_clock::now();
                    isMoving = true;
                    hasStart = true;

                    //  Gọi Greedy assign Orders cho drones

                    assignOrdersGreedy(drones, orders, nodes, edges);

                    logMessage("[DEBUG] assignOrdersGreedy trong while duoc goi!");
                }
            }
        }
        if (hasStart && hasNewOrder)
        {
            if (currentPage == "Home")
            {
                bool hasPendingOrder = false;
                for (const auto &o : orders)
                {
                    if (o.getStatus() != "moving")
                    {
                        hasPendingOrder = true;
                        break;
                    }
                }

                if (hasPendingOrder)
                {
                    logMessage("[SYSTEM] Co don hang moi, khoi dong lai drone");
                    cout << "[DEBUG] assignOrdersGreedy trong newOrder duoc goi!" << endl;
                    assignOrdersGreedy(drones, orders, nodes, edges);
                    isMoving = true;
                    hasNewOrder = false;
                    lastTime = chrono::high_resolution_clock::now();
                }
            }
        }
        // Vẽ nền
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 255);
        SDL_RenderClear(renderer);

        //  Sidebar
        if (sidebarVisible)
        {
            SDL_Rect sidebar = {0, 0, sidebarWidth, screenHeight};
            SDL_SetRenderDrawColor(renderer, sidebarColor.r, sidebarColor.g, sidebarColor.b, 255);
            SDL_RenderFillRect(renderer, &sidebar);

            // Các nút sidebar
            for (auto &btn : buttons)
            {
                SDL_Rect btnRect = btn.rect; // Xử lý btnRect.x = 0
                if (btn.selected)
                    SDL_SetRenderDrawColor(renderer, selectedColor.r, selectedColor.g, selectedColor.b, 255);
                else
                    SDL_SetRenderDrawColor(renderer, sidebarColor.r, sidebarColor.g, sidebarColor.b, 255);

                SDL_RenderFillRect(renderer, &btnRect);
                SDL_Texture *icon = nullptr;
                if (btn.label == "Home")
                    icon = homeIcon;
                else if (btn.label == "Drone")
                    icon = droneIcon;
                else if (btn.label == "Order")
                    icon = orderIcon;
                else if (btn.label == "Task")
                    icon = taskIcon;
                else if (btn.label == "Notification")
                    icon = notificationIcon;
                else if (btn.label == "Graph")
                    icon = graphIcon;

                if (icon)
                {
                    int iconSize = static_cast<int>(btnRect.h * 0.4);   // icon vừa với chiều cao button
                    int iconX = btnRect.x + 10;                         // cách viền trái 10px
                    int iconY = btnRect.y + (btnRect.h - iconSize) / 2; // căn giữa theo chiều cao

                    renderTexture(renderer, icon, iconX, iconY, iconSize, iconSize);
                }
                int fontHeight = TTF_FontHeight(font);

                // Vẽ label căn giữa theo chiều cao button
                int textX = btnRect.x + (btn.rect.h * 0.8) + 5; // cách icon 20px
                int textY = btnRect.y + (btnRect.h - fontHeight) / 2;
                renderText(renderer, font, btn.label, textX, textY, textColor);
            }
        }

        // Nút 3 gạch — luôn ở cạnh sidebar

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        for (int i = 0; i < 3; i++)
        {
            SDL_Rect line = {menuBtn.x + 10, menuBtn.y + 8 + i * 10, 30, 4};
            SDL_RenderFillRect(renderer, &line);
        }

        // Nội dung trang
        int contentX = sidebarVisible ? sidebarWidth + 20 : 20;

        if (currentPage == "Home")
        {
            renderHomePage(renderer, fontSmall, drones, nodes, edges, orders);

            if (isMoving)
            {
                auto currentTime = chrono::high_resolution_clock::now();
                float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
                lastTime = currentTime;
                // cout << "[FRAME] deltaTime=" << deltaTime << endl;

                bool anyFinished = false;
                for (auto &d : drones)
                {
                    d.updateMove(deltaTime);
                    if (d.getFinished())
                    {
                        anyFinished = true;
                        d.setFinished(false);
                    }
                }
                if (anyFinished)
                {

                    logMessage("[DEBUG] assignOrdersGreedy trong Finished duoc goi!");
                    assignOrdersGreedy(drones, orders, nodes, edges);
                }
            }
        }

        else if (currentPage == "Drone")
        {
            renderDronePage(renderer, font, drones, contentX);
        }

        else if (currentPage == "Order")
        {

            renderOrderPage(renderer, font, orders, contentX);
        }

        else if (currentPage == "Task")
        {
            renderTaskPage(renderer, font, tasks, contentX);
        }
        else if (currentPage == "Notification")
        {
            renderNotificationPage(renderer, font, notifications);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Lúc này mỗi giây chỉ ~60 vòng → deltaTime ≈ 0.016s đúng thực tế
    }

    TTF_CloseFont(font);
    TTF_Quit();
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(homeIcon);
    SDL_DestroyTexture(droneIcon);
    SDL_DestroyTexture(orderIcon);
    SDL_DestroyTexture(taskIcon);
    SDL_DestroyTexture(notificationIcon);
    SDL_DestroyTexture(graphIcon);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
