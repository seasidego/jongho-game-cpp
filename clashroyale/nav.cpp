#include "nav.h"
#include "raylib.h"
#include "game.h"
#include <iostream>

// to the dest ver
// std::vector<Vector2> Nav::nav(const Board& board, const Vector2& currentPos, const Vector2& destPos) {
//     const auto& grid = board.getGrid();
    
//     int currentYPos = currentPos.y / TileSize;
//     int currentXPos = currentPos.x / TileSize;

//     int destYPos = destPos.y / TileSize;
//     int destXPos = destPos.x / TileSize;

//     int count = 0;

//     std::vector<Vector2> route;

//     while (!(currentXPos == destXPos && currentYPos == destYPos)) {    
//         count++;
//         Vector2 minPos;
//         int minDis = 1000;
//         for (int i = -1; i <= 1; i++) {
//             for (int j = -1; j <= 1; j++) {
//                 int nextYPos = currentYPos + i;
//                 int nextXPos = currentXPos + j;

//                 if (nextYPos < 0 || nextYPos >= grid.size()) {
//                     continue;
//                 }
//                 const auto& line = grid[nextYPos];
//                 if (nextXPos < 0 || nextXPos >= line.size()) {
//                     continue;
//                 }

//                 int sum = std::abs(nextYPos - destYPos) + std::abs(nextXPos - destXPos);

//                 if (sum < minDis) {
//                     minDis = sum;
//                     minPos.x = nextXPos;
//                     minPos.y = nextYPos;
//                 }
//             }
//         }
//         route.emplace_back(minPos);
//         currentXPos = minPos.x;
//         currentYPos = minPos.y;
//         if (count >= 500) {
//             break;
//         }
//     }
    
//     return route;
// }

// one tile ver
// Vector2 Nav::nav(const Board& board, const Vector2& currentPos, const Vector2& destPos) {
//     const auto& grid = board.getGrid();
    
//     int currentYPos = currentPos.y / TileSize;
//     int currentXPos = currentPos.x / TileSize;

//     int destYPos = destPos.y / TileSize;
//     int destXPos = destPos.x / TileSize;

//     int count = 0;

//     // while (!(currentXPos == destXPos && currentYPos == destYPos)) {    
//     // }

//     Vector2 minPos;

//     if (currentXPos == destXPos && currentYPos == destYPos) {    
//         minPos.x = currentXPos;
//         minPos.y = currentYPos;
//         return minPos;
//     }

//     count++;
    
//     int minDis = 1000;
//     for (int i = -1; i <= 1; i++) {
//         for (int j = -1; j <= 1; j++) {

//             if (i == 0 && j == 0) {
//                 continue;
//             }

//             int nextYPos = currentYPos + i;
//             int nextXPos = currentXPos + j;

//             if (nextYPos < 0 || nextYPos >= grid.size()) {
//                 continue;
//             }
//             const auto& line = grid[nextYPos];
//             if (nextXPos < 0 || nextXPos >= line.size()) {
//                 continue;
//             }

//             if (!line[nextXPos].canCross()) {
//                 continue;
//             }

//             int sum = std::abs(nextYPos - destYPos) + std::abs(nextXPos - destXPos);

//             if (sum < minDis) {
//                 minDis = sum;
//                 minPos.x = nextXPos;
//                 minPos.y = nextYPos;
//             }
//         }
//     }
    
//     return minPos;
// }

// check all ver
// nav() {
//  if it is dest then return
//  for loop to check tiles around that can go.
//  for loop that tiles and recursive call nav(tiles)
// }
std::vector<Vector2> Nav::nav(const Board::Grid& grid, const Vector2& currentPos, const Vector2& destPos) {
    int count = 0;

    std::vector<Vector2> routeForPart;
    std::vector<Vector2> route;

    Vector2 currentTile = toTile(currentPos);
    Vector2 destTile = toTile(destPos);

    route = navPart(grid, currentTile, destTile, routeForPart, 0);
    
    for (auto& r : route) {
        std::cout << std::format("x: {} y: {}", r.x, r.y) << std::endl;
        r = toPos(r);
    }

    return route;
}

std::vector<Vector2> Nav::navPart(const Board::Grid& grid, const Vector2& currentTile, const Vector2& destTile, 
    std::vector<Vector2> route, int depth) {

    std::vector<Vector2> needCheckTile;
    route.emplace_back(currentTile);

    if (isEqual(currentTile, destTile)) {
        return route;
    }

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            Vector2 nextTile;
            nextTile.y = currentTile.y + i;
            nextTile.x = currentTile.x + j;

            if (i == 0 && j == 0) {
                continue;;
            }

            auto it = std::find_if(route.begin(), route.end(), [&nextTile](const auto& t) {
                return t.x == nextTile.x && t.y == nextTile.y;
            });

            if (it != route.end()) {
                continue;
            }

            if (nextTile.y < 0 || nextTile.y >= grid.size()) {
                continue;
            }

            const auto& line = grid[nextTile.y];
            if (nextTile.x < 0 || nextTile.x >= line.size()) {
                continue;
            }

            if (!line[nextTile.x].canCross()) {
                continue;
            }

            needCheckTile.emplace_back(nextTile);
        }
    }

    std::vector<std::vector<Vector2>> allRoute;

    for (const auto& n : needCheckTile) {
        allRoute.emplace_back(navPart(grid, n, destTile, route, ++depth));
    }

    int min = 100000;
    for (const auto& a : allRoute) {
        if (a.size() < min) {
            route = a;
            min = a.size();
        }
    }

    return route;
}

            