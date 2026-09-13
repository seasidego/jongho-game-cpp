#pragma once 
#include "game.h"
#include "board.h"
#include "raylib.h"

void UIMgr::init() {
    InitWindow(600, 800, "Raylib Simple Test");
    SetTargetFPS(60);
}

void UIMgr::print(const Board& b, const CardMrg& mrg) const {
    while (!WindowShouldClose() && run_) {
        BeginDrawing();
    
        ClearBackground(BLACK);
        
        //DrawText("Raylib is working!", startX_, startY_, 30, SKYBLUE);
        printBoard(b, mrg);

        EndDrawing();
    }
    CloseWindow();
}

void UIMgr::printBoard(const Board& board, const CardMrg& mrg) const {
    const auto& boardList = board.getBoard();
    int posx = 0;
    int posy = 0;
    std::for_each(boardList.begin(), boardList.end(), [this, &posx, &posy](const auto& b) {
        std::for_each(b.begin(), b.end(), [this, &posx, &posy](const auto& t) {
            DrawRectangleRec(Rectangle{StartPos.x + posx * TileSize, StartPos.y + posy * TileSize, TileSize, TileSize}, BLACK);
            DrawRectangleLinesEx(Rectangle{StartPos.x + posx * TileSize, StartPos.y + posy * TileSize, TileSize, TileSize}, 1.0, WHITE);
            posx++;
        });
        posx = 0;
        posy++;
    });

    const auto& cardList = mrg.getCards();
    std::for_each(cardList.begin(), cardList.end(), [this, &posx, &posy](const auto& c) {
        const auto* text = c->getShape();
        auto size = c->getSize() * TileSize;
        auto pos = c->getPos();
        float spacing = 0.;
        Vector2 textSize = MeasureTextEx(GetFontDefault(), text, size, spacing);
        Vector2 textPos = {
            pos.x + (size - textSize.x) / 2.0f,
            pos.y + (size - textSize.y) / 2.0f
        };
        auto recColor = (c->getTeam() == Card::Team::Red) ? RED : BLUE;

        DrawRectangleV(c->getPos(), Vector2{c->getSize() * TileSize, c->getSize() * TileSize}, BLACK);
        DrawTextEx(GetFontDefault(), text, textPos, size * 0.8, spacing, recColor);
    });
    
}

void UIMgr::stop() {
    run_ = false;
}

// void Game::startUI() {
//     uiMgr_.init();
// }

void Game::init() {
    uiMgr_.init();
    board_.init();
    cardMgr_.init();
}

void Game::endUI() {
    uiMgr_.stop();
}

const UIMgr& Game::getUIMgr() const {
    return uiMgr_;
}

void Game::print() {
    uiMgr_.print(board_, cardMgr_);
}