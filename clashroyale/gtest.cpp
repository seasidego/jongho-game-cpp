#include <gtest/gtest.h>
#include "clashroyale.h"
#include "raylib.h"

TEST(lifegame, addNumber) {
    // 1. 윈도우 창 생성 (가로 800, 세로 600, 창 제목)
    InitWindow(800, 600, "Raylib Simple Test");

    // 2. 목표 프레임 레이트 설정 (초당 60프레임)
    SetTargetFPS(60);

    // 3. 게임 루프 (창이 닫히거나 ESC를 누르기 전까지 무한 반복)
    while (!WindowShouldClose()) {
        
        // 4. 그리기 시작
        BeginDrawing();
        
        // 배경색을 검은색으로 지우기
        ClearBackground(BLACK);

        // 화면에 텍스트 그리기 (내용, X좌표, Y좌표, 글자크기, 색상)
        DrawText("Raylib is working!", 260, 280, 30, SKYBLUE);

        // 5. 그리기 끝 (화면에 출력)
        EndDrawing();
    }

    // 6. 윈도우 창 닫기 및 메모리 해제
    CloseWindow();
}

