#include "StatisticsPage.h"

vector<graphBoxes> gBox;

void drawPoint(SDL_Renderer *renderer, int cx, int cy, int r, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    for (int w = 0; w < r * 2; w++)
    {
        for (int h = 0; h < r * 2; h++)
        {
            int dx = r - w;
            int dy = r - h;
            if ((dx * dx + dy * dy) <= (r * r))
            {
                SDL_RenderDrawPoint(renderer, cx + dx, cy + dy);
            }
        }
    }
}

void drawGraph(SDL_Renderer *renderer, TTF_Font *font, graphBoxes gBox)
{
    //
    int margin = 80;
    int graphLeft = gBox.boxes.x + margin;
    int graphRight = gBox.boxes.x + gBox.boxes.w - margin;
    int graphTop = gBox.boxes.y + margin;
    int graphBottom = gBox.boxes.y + gBox.boxes.h - margin;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, graphLeft, graphTop, graphLeft, graphBottom);
    SDL_RenderDrawLine(renderer, graphLeft, graphBottom, graphRight - 140, graphBottom);

    vector<int> point1 = {10, 20, 25, 35, 40, 45};
    vector<int> point2 = {12, 25, 30, 40, 45, 50};

    int n = point1.size();
    int maxValue = 50;
    int graphWidth = graphRight - 140 - graphLeft;
    int graphHeight = graphBottom - graphTop;

    SDL_Color colorLine1 = {255, 99, 71, 255}; // do cam
    SDL_Color colorLine2 = {65, 105, 225, 255};

    for (int i = 0; i < n - 1; i++)
    {
        int x1 = graphLeft + (graphWidth / (n - 1)) * i;
        int x2 = graphLeft + (graphWidth / (n - 1)) * (i + 1);

        int y1A = graphBottom - (point1[i] * graphHeight / maxValue);
        int y2A = graphBottom - (point1[i + 1] * graphHeight / maxValue);
        int y1D = graphBottom - (point2[i] * graphHeight / maxValue);
        int y2D = graphBottom - (point2[i + 1] * graphHeight / maxValue);

        SDL_SetRenderDrawColor(renderer, colorLine1.r, colorLine1.g, colorLine1.b, colorLine1.a);
        SDL_RenderDrawLine(renderer, x1, y1A, x2, y2A);
        drawPoint(renderer, x1, y1A, 3, colorLine1);

        SDL_SetRenderDrawColor(renderer, colorLine2.r, colorLine2.g, colorLine2.b, colorLine2.a);
        SDL_RenderDrawLine(renderer, x1, y1D, x2, y2D);
        drawPoint(renderer, x1, y1D, 3, colorLine2);
    }

    // chu thich
    int noteLeft = graphLeft + graphWidth + 40;
    int noteRight = graphRight - 40;
    int noteTop = graphTop + 20;
    int noteBottom = graphBottom - 20;

    int noteW = 120, noteH = 20;

    SDL_Rect noteRect = {noteLeft, noteTop, noteW, noteH};

    int textW, textH;
    string m = gBox.s[0];
    string h = gBox.s[1];
    TTF_SizeText(font, m.c_str(), &textW, &textH);

    drawPoint(renderer, noteRect.x + 10, noteRect.y + noteH / 2, 4, colorLine1);
    drawPoint(renderer, noteRect.x + 10, noteRect.y + 40 + noteH / 2, 4, colorLine2);
    renderText(renderer, font, m, noteRect.x + (noteW - textW) / 2, noteRect.y + (noteH - textH) / 2, colorLine1);
    renderText(renderer, font, h, noteRect.x + (noteW - textW) / 2, noteRect.y + 40 + (noteH - textH) / 2, colorLine2);
}

void renderStatisticsPage(SDL_Renderer *renderer, TTF_Font *font, int startX)
{
    int winW, winH;
    SDL_GetRendererOutputSize(renderer, &winW, &winH);
    // phan chia 4 ô

    // giới hạn vùng nội dung
    int contentLeft = startX + 40;
    int contentRight = winW - 40;
    int contentTop = 100;
    int contentBottom = winH - 40;

    int contentWidth = contentRight - contentLeft;
    int contentHeight = contentBottom - contentTop;

    // chia 4 luoi
    int cellW = contentWidth / 2 - 40;
    int cellH = contentHeight / 2 - 40;

    SDL_Rect boxes[4];
    boxes[0] = {contentLeft, contentTop, cellW, cellH};
    vector<string> se;
    se.push_back("Astar");
    se.push_back("Dijkstra");
    gBox.push_back({boxes[0], se});

    boxes[1] = {contentLeft + cellW + 20, contentTop, cellW, cellH};
    se.clear();
    se.push_back("Greedy");
    se.push_back("Hungray");
    gBox.push_back({boxes[1], se});
    boxes[2] = {contentLeft, contentTop + cellH + 20, cellW, cellH};
    se.clear();
    se.push_back("Orders");
    se.push_back("Drones");
    gBox.push_back({boxes[2], se});
    boxes[3] = {contentLeft + cellW + 20, contentTop + cellH + 20, cellW, cellH};
    se.clear();
    se.push_back("Time");
    se.push_back("Quantities");
    gBox.push_back({boxes[3], se});
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (auto &b : boxes)
    {
        SDL_RenderDrawRect(renderer, &b);
    }
    for (auto &b : gBox)
    {
        drawGraph(renderer, font, b);
    }
}

// 1536 8641536