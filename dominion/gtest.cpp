#include <gtest/gtest.h>
#include "dominion.h"

TEST(SampleTest, addNumber) {
    EXPECT_EQ(3, 1 + 2);
}

TEST(SampleTest, Buy) {
    Game game;
    game.addPlayer();
    game.initRegistry();
    game.initSupply();
    game.setStartCard();
    game.resetTurnState();

    game.buyCard();
    game.print();
    std::cout << "end" << std::endl;
}
