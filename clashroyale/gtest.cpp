#include <gtest/gtest.h>
#include "clashroyale.h"
#include "raylib.h"
#include "game.h"

TEST(clashroyale, toTile) {
    // Game game;
    // game.init();
    // game.play();

    auto tile = toTile(Vector2{100, 200});
    EXPECT_EQ(5, tile.x);
    EXPECT_EQ(10, tile.y);

    auto pos = toPos(Vector2{5, 10});
    EXPECT_EQ(100, pos.x);
    EXPECT_EQ(200, pos.y);

    auto eq = isEqual(Vector2{5, 10}, Vector2{5, 10});
    EXPECT_EQ(true, eq);
       
}

TEST(clashroyale, play) {
    Game game;
    game.init();
    game.play();
}