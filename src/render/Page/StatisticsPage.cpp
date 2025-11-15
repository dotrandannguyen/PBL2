#include "StatisticsPage.h"

vector<graphBoxes> gBox;
vector<float> greedyTimes;
vector<float> hungaryTimes;

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
    SDL_RenderDrawLine(renderer, graphLeft, graphTop - 30, graphLeft, graphBottom);
    SDL_RenderDrawLine(renderer, graphLeft, graphBottom, graphRight - 140, graphBottom);

    vector<float> point1 = greedyTimes;
    vector<float> point2 = hungaryTimes;

    int n = point1.size();
    int n1 = point2.size();
    // tinh maxVlue để scale
    float maxValue = 0;
    for (auto v : point1)
    {
        maxValue = max(maxValue, v);
    }

    for (auto v : point2)
    {
        maxValue = max(maxValue, v);
    }
    maxValue = (maxValue / 10 + 1) * 10; // lam tron

    int graphWidth = graphRight - 140 - graphLeft;
    int graphHeight = graphBottom - graphTop;

    // truc Ox:
    int labelW = 0, labelH = 0;
    string sampleLable = to_string(max(0, n - 1));
    TTF_SizeText(font, sampleLable.c_str(), &labelW, &labelH);

    float pxPerIndex = (n > 1) ? (graphWidth / (float)(n - 1)) : graphWidth;
    int stepX = max(1, (int)ceil((labelW + 8) / pxPerIndex)); // 8px them

    for (int i = 0; i < n; i += stepX)
    {
        int x = graphLeft + (graphWidth / (float)(n - 1)) * i;
        renderText(renderer, font, to_string(i), x - labelW / 2, graphBottom + 5, {0, 0, 0, 255});
        if ((n - 1) % stepX != 0)
        {
            int xLast = graphLeft + (int)round((graphWidth / (float)(n - 1)) * (n - 1));
            TTF_SizeText(font, to_string(n - 1).c_str(), &labelW, &labelH);
            renderText(renderer, font, to_string(n - 1), xLast - labelW / 2, graphBottom + 5, {0, 0, 0, 255});
        }
    }

    // truc Oy
    auto niceStep = [](float maxV, int maxTicks)
    {
        if (maxV <= 0)
            return 1.0f;
        float rough = maxV / maxTicks;
        float mag = powf(10.0f, floorf(log10f(rough)));
        float norm = rough / mag;
        float niceNorm = (norm < 1.5f) ? 1.f : (norm < 3.f) ? 2.f
                                           : (norm < 7.f)   ? 5.f
                                                            : 10.f;
        return niceNorm * mag; // 1, 2, 5, 10 ... × 10^k
    };

    int maxTicks = 6;
    float stepY = niceStep(maxValue, maxTicks);

    for (float v = 0; v <= maxValue + 0.5f * stepY; v += stepY)
    {
        if (v != 0)
        {
            int y = graphBottom - (int)round((v * graphHeight) / maxValue);
            SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
            SDL_RenderDrawLine(renderer, graphLeft, y, graphRight - 140, y);
            renderText(renderer, font, to_string((int)round(v)), graphLeft - 35, y - 8, {0, 0, 0, 255});
        }
    }

    SDL_Color colorLine1 = {255, 99, 71, 255}; // do cam
    SDL_Color colorLine2 = {65, 105, 225, 255};

    for (int i = 0; i < n - 1; i++)
    {
        float x1 = graphLeft + (graphWidth / (float)(n - 1)) * i;
        float x2 = graphLeft + (graphWidth / (float)(n - 1)) * (i + 1);

        float y1A = graphBottom - (point1[i] * graphHeight / (float)maxValue);
        float y2A = graphBottom - (point1[i + 1] * graphHeight / (float)maxValue);

        SDL_SetRenderDrawColor(renderer, colorLine1.r, colorLine1.g, colorLine1.b, colorLine1.a);
        SDL_RenderDrawLine(renderer, (int)x1, (int)y1A, (int)x2, (int)y2A);
        drawPoint(renderer, (int)x1, (int)y1A, 3, colorLine1);
    }

    for (int i = 0; i < n1 - 1; i++)
    {
        float x1 = graphLeft + (graphWidth / (float)(n1 - 1)) * i;
        float x2 = graphLeft + (graphWidth / (float)(n1 - 1)) * (i + 1);

        float y1D = graphBottom - (point2[i] * graphHeight / (float)maxValue);
        float y2D = graphBottom - (point2[i + 1] * graphHeight / (float)maxValue);

        SDL_SetRenderDrawColor(renderer, colorLine2.r, colorLine2.g, colorLine2.b, colorLine2.a);
        SDL_RenderDrawLine(renderer, (int)x1, (int)y1D, (int)x2, (int)y2D);
        drawPoint(renderer, (int)x1, (int)y1D, 3, colorLine2);
    }

    // chu thich
    int legendWidth = 140;
    int legendLeft = graphRight - legendWidth;
    int legendTop = graphTop + 20;

    SDL_Rect noteRect = {legendLeft + 20, legendTop, legendWidth, 20};

    int textW, textH;
    string m = gBox.s[0];
    string h = gBox.s[1];
    TTF_SizeText(font, m.c_str(), &textW, &textH);

    drawPoint(renderer, noteRect.x + 20, noteRect.y + noteRect.h / 2, 4, colorLine1);
    drawPoint(renderer, noteRect.x + 20, noteRect.y + 40 + noteRect.h / 2, 4, colorLine2);
    renderText(renderer, font, m, noteRect.x + (noteRect.w - textW) / 2, noteRect.y + (noteRect.h - textH) / 2, colorLine1);
    renderText(renderer, font, h, noteRect.x + (noteRect.w - textW) / 2, noteRect.y + 40 + (noteRect.h - textH) / 2, colorLine2);
}

void renderStatisticsPage(SDL_Renderer *renderer, TTF_Font *font, int startX)
{
    gBox.clear();
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