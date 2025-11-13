#include "StatisticsPage.h"

vector<graphBoxes> gBox;
vector<float> greedyTimes;

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

    // vector<int> point1 = {10, 12, 15, 17, 19, 20, 22, 24, 25, 27, 28, 30, 31, 33, 35, 36, 38, 39, 40, 42};
    vector<float> point1 = greedyTimes;
    // vector<int> point2 = {9, 11, 13, 15, 18, 19, 21, 23, 25, 26, 27, 29, 30, 32, 34, 35, 36, 38, 39, 41};

    int n = point1.size();

    // tinh maxVlue để scale
    float maxValue = 0;
    for (auto v : point1)
    {
        maxValue = max(maxValue, v);
    }

    // for (auto v : point2)
    // {
    //     maxValue = max(maxValue, v);
    // }
    maxValue = (maxValue / 10 + 1) * 10; // lam tron

    int graphWidth = graphRight - 140 - graphLeft;
    int graphHeight = graphBottom - graphTop;

    SDL_Color colorLine1 = {255, 99, 71, 255}; // do cam
    SDL_Color colorLine2 = {65, 105, 225, 255};

    for (int i = 0; i < n - 1; i++)
    {
        float x1 = graphLeft + (graphWidth / (float)(n - 1)) * i;
        float x2 = graphLeft + (graphWidth / (float)(n - 1)) * (i + 1);

        float y1A = graphBottom - (point1[i] * graphHeight / (float)maxValue);
        float y2A = graphBottom - (point1[i + 1] * graphHeight / (float)maxValue);
        // float y1D = graphBottom - (point2[i] * graphHeight / (float)maxValue);
        // float y2D = graphBottom - (point2[i + 1] * graphHeight / (float)maxValue);

        SDL_SetRenderDrawColor(renderer, colorLine1.r, colorLine1.g, colorLine1.b, colorLine1.a);
        SDL_RenderDrawLine(renderer, (int)x1, (int)y1A, (int)x2, (int)y2A);
        drawPoint(renderer, (int)x1, (int)y1A, 3, colorLine1);

        SDL_SetRenderDrawColor(renderer, colorLine2.r, colorLine2.g, colorLine2.b, colorLine2.a);
        // SDL_RenderDrawLine(renderer, (int)x1, (int)y1D, (int)x2, (int)y2D);
        // drawPoint(renderer, (int)x1, (int)y1D, 3, colorLine2);

        // truc Ox:

        int x = graphLeft + (graphWidth / (float)(n - 1)) * i;
        renderText(renderer, font, to_string(i), x - 5, graphBottom + 5, {0, 0, 0, 255});

        // truc Oy:
        int y = graphBottom - (point1[i] * graphHeight / (int)maxValue);
        renderText(renderer, font, to_string((int)point1[i]), graphLeft - 30, y - 8, {0, 0, 0, 255});
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
    se.push_back("Greedy");
    se.push_back("Hungary");
    gBox.push_back({boxes[0], se});

    boxes[1] = {contentLeft + cellW + 20, contentTop, cellW, cellH};
    se.clear();
    se.push_back("Astar");
    se.push_back("Dijkstra");
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