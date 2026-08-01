#include <gtest/gtest.h>
#include "dominion.h"

TEST(SampleTest, addNumber) {
    EXPECT_EQ(3, 1 + 2);
}

TEST(SampleTest, Buy) {
    Game game;
    game.init();

    game.buyCard(0);
    EXPECT_EQ(59, game.getSupplyForTest().getCardsForTest().at(0).second);

    game.print();
    std::cout << "end" << std::endl;
}

// TEST(SampleTest, Draw) {
//     Game game;
//     game.init();

//     game.

//     game.print();
//     std::cout << "end" << std::endl;
// }
