#include "Renderer.h"

using namespace std;
bool isMouseInside(const SDL_Rect &rect, int mx, int my)
{
    return (
        mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h);
}

void renderText(SDL_Renderer *renderer, TTF_Font *font, const string &text, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

SDL_Texture *loadTexture(SDL_Renderer *renderer, const string &file)
{
    {
        SDL_Surface *surface = IMG_Load(file.c_str());
        if (!surface)
        {
            cout << "IMG_Load error: " << IMG_GetError() << endl;
            return nullptr;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
        if (!texture)
            cout << "SDL_CreateTextureFromSurface error: " << SDL_GetError() << endl;

        return texture;
    }
}
void renderTexture(SDL_Renderer *renderer, SDL_Texture *texture, int x, int y, int w, int h)
{
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    dst.w = w; // chiều rộng hiển thị
    dst.h = h; // chiều cao hiển thị
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

float calculateDistance(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void runAlgorithms(const vector<Drone> &drones,
                   const vector<Order> &orders,
                   const vector<Node> &nodes,
                   const vector<Edge> &edges,
                   const vector<Task> &tasks,
                   bool isAlgorithm)
{
    // Snapshot dữ liệu gốc
    vector<Drone> d1 = drones, d2 = drones;
    vector<Order> o1 = orders, o2 = orders, o3 = orders;
    vector<Node> n1 = nodes, n2 = nodes;
    vector<Edge> e1 = edges, e2 = edges;
    vector<Task> t1 = tasks, t2 = tasks;
    if (isAlgorithm)
    {

        // Chạy Hungarian

        assignOrdersHungarian(d2, o2, n2, e2, t2);

        // cout << "[INFO] Hungary (ngam) hoat dong" << endl;
    }
    else
    {

        // Chạy Greedy

        assignOrdersGreedy(d1, o1, n1, e1, t1);
        // cout << "[INFO] Greedy (ngam) hoat dong" << endl;
    }

    for (auto &order : o3)
    {
        string start = order.getPickupLocation();
        string end = order.getDropoffLocation();

        int countAstar = astarNodeVisited(start, end);
        int countDijkstra = dijkstraNodeVisited(start, end);

        astarVisited.push_back(countAstar);
        dijkstraVisited.push_back(countDijkstra);
    }
}
