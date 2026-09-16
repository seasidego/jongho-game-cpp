#include "nav.h"
#include "raylib.h"
#include "game.h"

std::vector<Vector2> Nav::nav(const Board& board, const Vector2& currentPos, const Vector2& destPos) {
    const auto& grid = board.getGrid();
    
    int currentYPos = currentPos.y / TileSize;
    int currentXPos = currentPos.x / TileSize;

    int destYPos = destPos.y / TileSize;
    int destXPos = destPos.x / TileSize;

    int count = 0;

    std::vector<Vector2> route;

    while (!(currentXPos == destXPos && currentYPos == destYPos)) {    
        count++;
        Vector2 minPos;
        int minDis = 1000;
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nextYPos = currentYPos + i;
                int nextXPos = currentXPos + j;

                if (nextYPos < 0 || nextYPos >= grid.size()) {
                    continue;
                }
                const auto& line = grid[nextYPos];
                if (nextXPos < 0 || nextXPos >= line.size()) {
                    continue;
                }

                int sum = std::abs(nextYPos - destYPos) + std::abs(nextXPos - destXPos);

                if (sum < minDis) {
                    minDis = sum;
                    minPos.x = nextXPos;
                    minPos.y = nextYPos;
                }
            }
        }
        route.emplace_back(minPos);
        currentXPos = minPos.x;
        currentYPos = minPos.y;
        if (count >= 500) {
            break;
        }
    }
    
    return route;
}