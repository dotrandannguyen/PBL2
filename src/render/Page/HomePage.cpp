#include "HomePage.h"

// Biến toàn cục để lưu drone nào đang được chọn
int selectedDroneIndex = -1;

SDL_Point getDronePosXY(const string &pos)
{
    if (pos.size() < 2)
        return {0, 0};

    char zone = pos[0];
    int index = pos[1] - '0';

    int baseX = 100 * (zone - 'A' + 1);
    int baseY = 100 * index;

    return {baseX + 100, baseY + 100};
}

void renderHomePage(SDL_Renderer *renderer, TTF_Font *fontSmall, const std::vector<Drone> &drones, const std::vector<Node> &nodes, const std::vector<Edge> &edges)
{
    SDL_Color textColor = {0, 0, 0, 255};

    // Vẽ từng drone
    for (size_t i = 0; i < drones.size(); ++i)
    {
        const auto &d = drones[i];
        SDL_Rect droneRect = {static_cast<int>(d.getX()), static_cast<int>(d.getY()), 20, 20};

        // Màu drone theo trạng thái
        if (d.getStatus() == "idle")
            SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
        else if (d.getStatus() == "moving")
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
        else
            SDL_SetRenderDrawColor(renderer, 0, 100, 255, 255);

        // Nếu là drone được chọn thì thêm viền xanh dương
        if (static_cast<int>(i) == selectedDroneIndex)
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            SDL_Rect outline = {droneRect.x - 2, droneRect.y - 2, droneRect.w + 4, droneRect.h + 4};
            SDL_RenderDrawRect(renderer, &outline);
        }

        SDL_RenderFillRect(renderer, &droneRect);

        // Chỉ hiển thị DroneID nếu drone đang được chọn
        if (static_cast<int>(i) == selectedDroneIndex)
        {
            renderText(renderer, fontSmall, d.getDroneID(),
                       static_cast<int>(d.getX()) + 25,
                       static_cast<int>(d.getY()) - 5,
                       textColor);
        }
    }
    // vẽ từng node
    for (auto &n : nodes)
    {
        SDL_Rect nodeRect = {static_cast<int>(n.getX()), static_cast<int>(n.getY()), 14, 14};
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255); // Node màu đỏ
        SDL_RenderFillRect(renderer, &nodeRect);

        renderText(renderer, fontSmall, n.getNodeID(),
                   static_cast<int>(n.getX()) - 5,
                   static_cast<int>(n.getY()) - 18,
                   textColor);
    }
    // vẽ các cạnh giữa các node
    for (auto &e : edges)
    {
        const Node *startNode = nullptr;
        const Node *endNode = nullptr;

        for (auto &n : nodes)
        {
            if (n.getNodeID() == e.getStartNode())
                startNode = &n;
            if (n.getNodeID() == e.getEndNode())
                endNode = &n;
        }

        if (startNode && endNode)
        {
            SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
            SDL_RenderDrawLine(renderer,
                               static_cast<int>(startNode->getX()) + 10,
                               static_cast<int>(startNode->getY()) + 10,
                               static_cast<int>(endNode->getX()) + 10,
                               static_cast<int>(endNode->getY()) + 10);
        }
    }

    // Lấy kích thước cửa sổ
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);

    // Vẽ nút Add Drone ở góc phải bên dưới
    int btnW = 120, btnH = 40;
    SDL_Rect addBtn = {w - btnW - 20, h - btnH - 20, btnW, btnH}; // cách viền 20 px
    SDL_SetRenderDrawColor(renderer, 0, 150, 255, 255);
    SDL_RenderFillRect(renderer, &addBtn);
    renderText(renderer, fontSmall, "Add Drone", addBtn.x + 10, addBtn.y + 10, {255, 255, 255, 255});

    SDL_Rect addNodeBtn = {w - 2 * btnW - 40, h - btnH - 20, btnW, btnH};
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 255);
    SDL_RenderFillRect(renderer, &addNodeBtn);
    renderText(renderer, fontSmall, "Add Node", addNodeBtn.x + 10, addNodeBtn.y + 10, {255, 255, 255, 255});
}

// Xử lý click nút Add Drone

void handleHomePageDroneClick(SDL_Renderer *renderer, int mx, int my, vector<Drone> &drones, const vector<Node> &nodes)
{
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h);
    int btnW = 120, btnH = 40;
    SDL_Rect addBtn = {w - btnW - 20, h - btnH - 20, btnW, btnH};

    if (isMouseInside(addBtn, mx, my))
    {
        int idNum = drones.size() + 1;
        string newID = "D00" + to_string(idNum);
        string name = "Drone_" + to_string(idNum);

        // Mặc định spawn ở node 1 hoặc node 2
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

        Drone newDrone(newID, name, x, y, 40.0f, 100, "idle", startNodeID);

        drones.push_back(newDrone);
        writeDronesToFile("D:/Drone-project/src/data/Drone.txt", drones);
        return;
    }
    // Kiểm tra click vào drone nào đó
    bool clickedOnDrone = false;
    for (size_t i = 0; i < drones.size(); ++i)
    {
        SDL_Rect droneRect = {static_cast<int>(drones[i].getX()), static_cast<int>(drones[i].getY()), 20, 20};
        if (mx >= droneRect.x && mx <= droneRect.x + droneRect.w &&
            my >= droneRect.y && my <= droneRect.y + droneRect.h)
        {
            selectedDroneIndex = static_cast<int>(i);
            clickedOnDrone = true;
            break;
        }
    }

    // Nếu không click vào drone nào -> bỏ chọn
    if (!clickedOnDrone)
        selectedDroneIndex = -1;
}

// // Xử lý click chọn vị trí drone mới
// void handleAddDroneClick(int mx, int my, vector<Drone> &drones)
// {
//     if (!isAddingDrone)
//         return;

//     int idNum = drones.size() + 1;
//     string newID = "D00" + to_string(idNum);
//     string name = "Drone_" + to_string(idNum);

//     // Tạo drone mới trực tiếp với tọa độ click
//     Drone newDrone(newID, name, static_cast<float>(mx), static_cast<float>(my), 40.0f, 100, "idle");
//     drones.push_back(newDrone);

//     writeDronesToFile("D:/Drone-project/src/data/Drone.txt", drones);

//     isAddingDrone = false;
// }

void handleHomePageNodeClick(SDL_Renderer *renderer, int mx, int my)
{
    int w, h;
    SDL_GetRendererOutputSize(renderer, &w, &h); // lấy đúng renderer
    int btnW = 120, btnH = 40;
    SDL_Rect addNodeBtn = {w - 2 * btnW - 40, h - btnH - 20, btnW, btnH};
    if (isMouseInside(addNodeBtn, mx, my))
    {
        isAddingNode = true;
    }
}

void handleAddNodeClick(int mx, int my, vector<Node> &nodes, vector<Edge> &edges)
{
    if (!isAddingNode)
        return;

    int idNum = nodes.size() + 1;
    string newID = "N0" + to_string(idNum);
    string name = "Node_" + to_string(idNum);

    Node newNode(newID, name, static_cast<float>(mx), static_cast<float>(my));
    nodes.push_back(newNode);

    writeNodesToFile("D:/Drone-project/src/data/Node.txt", nodes);

    // --- THÊM EDGE MỚI ---
    int nextEdgeID = edges.empty() ? 1 : edges.back().getEdgeID() + 1;

    // Mỗi node mới sẽ nối với tất cả node khác
    for (size_t i = 0; i < nodes.size() - 1; ++i)
    {
        const Node &other = nodes[i];
        float dist = calculateDistance(newNode.getX(), newNode.getY(), other.getX(), other.getY());

        // Edge 1 chiều (nếu bạn muốn 2 chiều thì tạo thêm edge ngược lại)
        edges.emplace_back(nextEdgeID++, newNode.getNodeID(), other.getNodeID(), dist);
    }

    // Ghi toàn bộ edges vào file
    writeEdgesToFile("D:/Drone-project/src/data/Edge.txt", edges);
    isAddingNode = false;
}