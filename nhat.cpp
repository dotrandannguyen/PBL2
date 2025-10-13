// rect.cpp
#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    const int WIN_W = 800;
    const int WIN_H = 600;
    SDL_Window *win = SDL_CreateWindow("SDL2 Rectangle Example",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WIN_W, WIN_H,
                                       SDL_WINDOW_SHOWN);
    if (!win)
    {
        std::cerr << "CreateWindow Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // Use accelerated renderer with vsync if available
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!ren)
    {
        std::cerr << "CreateRenderer Error: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event e;

    // Rectangle properties (you can change these)
    SDL_Rect rect;
    rect.x = 150;
    rect.y = 120;
    rect.w = 500;
    rect.h = 360;

    // Example: allow moving rectangle with arrow keys and resizing with +/- keys
    const int MOVE_STEP = 10;
    const int RESIZE_STEP = 10;

    while (running)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                running = false;
            else if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_LEFT:
                    rect.x -= MOVE_STEP;
                    break;
                case SDLK_RIGHT:
                    rect.x += MOVE_STEP;
                    break;
                case SDLK_UP:
                    rect.y -= MOVE_STEP;
                    break;
                case SDLK_DOWN:
                    rect.y += MOVE_STEP;
                    break;
                case SDLK_PLUS:
                case SDLK_EQUALS:
                    rect.w += RESIZE_STEP;
                    rect.h += RESIZE_STEP;
                    break; // '=' key usually same as '+'
                case SDLK_MINUS:
                    rect.w = std::max(10, rect.w - RESIZE_STEP);
                    rect.h = std::max(10, rect.h - RESIZE_STEP);
                    break;
                default:
                    break;
                }
            }
            // optional: mouse drag to move rect
            else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
            {
                int mx = e.button.x, my = e.button.y;
                if (mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h)
                {
                    // on click inside rect, center it to mouse
                    rect.x = mx - rect.w / 2;
                    rect.y = my - rect.h / 2;
                }
            }
        }

        // Clear screen (background)
        SDL_SetRenderDrawColor(ren, 30, 30, 30, 255); // dark gray background
        SDL_RenderClear(ren);

        // Draw filled rectangle
        SDL_SetRenderDrawColor(ren, 70, 130, 180, 255); // steel-blue fill
        SDL_RenderFillRect(ren, &rect);

        // Draw rectangle border (outline)
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); // white border
        SDL_RenderDrawRect(ren, &rect);

        // Present
        SDL_RenderPresent(ren);

        // small delay if you want (renderer with vsync probably already caps)
        SDL_Delay(10);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
