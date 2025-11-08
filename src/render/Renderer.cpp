#include "Renderer.h"
#include <string>
#include <cmath>
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
