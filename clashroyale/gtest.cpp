#include <gtest/gtest.h>
#include "clashroyale.h"
#include "raylib.h"
#include "game.h"
#include "board.h"

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
    // Game game;
    // game.init();
    // game.play();
}

TEST(clashroyale, nav) {
    {
        Board::Grid grid;
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(true)});
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(true)});

        Nav nav;
        const auto route = nav.nav(grid, toPos({0, 0}), toPos({1, 1}));

        EXPECT_TRUE(isEqualRoute(route, std::vector<Vector2>{toPos({0, 0}), toPos({1, 1})}));
    }
    
    {
        Board::Grid grid;
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(true), Tile(true)});
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(true), Tile(true)});
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(true), Tile(true)});

        Nav nav;
        const auto route = nav.nav(grid, toPos({0, 0}), toPos({2, 2}));

        EXPECT_TRUE(isEqualRoute(route, std::vector<Vector2>{toPos({0, 0}), toPos({1, 1}), toPos({2, 2})}));
    }

    {
        Board::Grid grid;
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(true), Tile(true)});
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(false), Tile(true)});
        grid.emplace_back(std::vector<Tile>{Tile(true), Tile(true), Tile(true)});

        Nav nav;
        const auto route = nav.nav(grid, toPos({0, 0}), toPos({2, 2}));

        EXPECT_TRUE(isEqualRoute(route, std::vector<Vector2>{toPos({0, 0}), toPos({1, 0}), toPos({2, 1}), toPos({2, 2})}));
    }
}