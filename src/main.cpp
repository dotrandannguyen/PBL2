#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include "D:\Drone-project\src\render\Renderer.h"

using namespace std;

struct Button
{
    SDL_Rect rect;
    string label;
    bool selected;
};

void renderText(SDL_Renderer *renderer, TTF_Font *font, const string &text, int x, int y, SDL_Color color)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dst = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &dst);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

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

    SDL_Window *window = SDL_CreateWindow("Dashboard - SDL2",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          1280, 720,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color bgColor = {245, 247, 250, 255};
    SDL_Color sidebarColor = {23, 42, 69, 255};
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color selectedColor = {255, 174, 66, 255};

    TTF_Font *font = TTF_OpenFont("C:/Windows/Fonts/segoeui.ttf", 22);
    if (!font)
    {
        cout << "Không tìm thấy font!\n";
        return 1;
    }

    vector<Button> buttons = {
        {{0, 100, 190, 50}, "Home", true},
        {{0, 160, 190, 50}, "Drone", false},
        {{0, 220, 190, 50}, "Task", false},
        {{0, 280, 190, 50}, "Notification", false},
        {{0, 340, 190, 50}, "Order", false},
        {{0, 400, 190, 50}, "Graph", false}};

    string currentPage = "Home";

    bool quit = false;
    bool sidebarVisible = true;
    int sidebarWidth = 200; // Chiều rộng sidebar
    SDL_Event e;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                int mx = e.button.x;
                int my = e.button.y;

                //  Nút 3 gạch — luôn nằm sát mép sidebar
                SDL_Rect menuBtn = {sidebarWidth + 10, 20, 50, 40};
                if (isMouseInside(menuBtn, mx, my))
                {
                    sidebarVisible = !sidebarVisible;
                    sidebarWidth = sidebarVisible ? 200 : 0; // Toggle width
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
            }
        }

        // Vẽ nền
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, 255);
        SDL_RenderClear(renderer);

        //  Sidebar
        if (sidebarVisible)
        {
            SDL_SetRenderDrawColor(renderer, sidebarColor.r, sidebarColor.g, sidebarColor.b, 255);
            SDL_Rect sidebar = {0, 0, sidebarWidth - 10, 720}; // Chừa 10px cho nút
            SDL_RenderFillRect(renderer, &sidebar);

            // Các nút sidebar
            for (auto &btn : buttons)
            {
                if (btn.selected)
                    SDL_SetRenderDrawColor(renderer, selectedColor.r, selectedColor.g, selectedColor.b, 255);
                else
                    SDL_SetRenderDrawColor(renderer, sidebarColor.r, sidebarColor.g, sidebarColor.b, 255);

                SDL_RenderFillRect(renderer, &btn.rect);
                renderText(renderer, font, btn.label, 30, btn.rect.y + 10, textColor);
            }
        }

        //  Nút 3 gạch — luôn ở cạnh sidebar
        SDL_Rect menuBtn = {sidebarWidth + 10, 20, 50, 40};
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        for (int i = 0; i < 3; i++)
        {
            SDL_Rect line = {menuBtn.x + 10, menuBtn.y + 8 + i * 10, 30, 4};
            SDL_RenderFillRect(renderer, &line);
        }

        // Nội dung trang
        int contentX = sidebarVisible ? 600 : 300;
        renderText(renderer, font, "Page: " + currentPage, contentX, 350, {0, 0, 0, 255});

        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
