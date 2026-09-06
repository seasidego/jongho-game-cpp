#pragma once 
#include "game.h"
#include "board.h"
#include "raylib.h"

void UIMgr::init() {
    InitWindow(600, 1000, "Raylib Simple Test");
    SetTargetFPS(60);
}

void UIMgr::print(const Board& b) const {
    while (!WindowShouldClose() && run_) {
        BeginDrawing();
    
        ClearBackground(BLACK);
        
        // DrawText("Raylib is working!", startX_, startY_, 30, SKYBLUE);
        printBoard(b);

        EndDrawing();
    }
    CloseWindow();
}

void UIMgr::printBoard(const Board& board) const {
    const auto& boardList = board.getBoard();
    int posx = 0;
    int posy = 0;
    DrawText("T", startX_, startY_, tileSize_, SKYBLUE);
    std::for_each(boardList.begin(), boardList.end(), [this, &posx, &posy](const auto& b) {
        std::for_each(b.begin(), b.end(), [this, &posx, &posy](const auto& t) {
            DrawText("T", startX_ + posx * tileSize_, startY_ + posy * tileSize_, tileSize_, SKYBLUE);
            posx++;
        });
        posy++;
    });
}

void UIMgr::stop() {
    run_ = false;
}

void Game::startUI() {
    UIMgr_.init();
}

void Game::endUI() {
    UIMgr_.stop();
}

const UIMgr& Game::getUIMgr() const {
    return UIMgr_;
}

void Game::print() {
    UIMgr_.print(board_);
}