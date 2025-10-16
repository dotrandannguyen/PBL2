#include "Renderer.h"

bool isMouseInside(const SDL_Rect &rect, int mx, int my)
{
    return (
        mx >= rect.x && mx <= rect.x + rect.w && my >= rect.y && my <= rect.y + rect.h);
}