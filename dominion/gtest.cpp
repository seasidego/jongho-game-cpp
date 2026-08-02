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
    EXPECT_EQ(RetCode::NoEnoughBuy, game.buyCard(0));

    // game.print();
    // std::cout << "end" << std::endl;
}

TEST(SampleTest, DrawAndDiscard) {
    Game game;
    game.init();

    EXPECT_EQ(RetCode::Success, game.draw(5));
    EXPECT_EQ(5, game.getPlayerForTest().getHandForTest().getSize());
    EXPECT_EQ(0, game.getPlayerForTest().getDiscardForTest().getSize());
    EXPECT_EQ(5, game.getPlayerForTest().getDeckForTest().getSize());

    game.discardAll();


    EXPECT_EQ(RetCode::Success, game.draw(5));
    EXPECT_EQ(5, game.getPlayerForTest().getHandForTest().getSize());
    EXPECT_EQ(5, game.getPlayerForTest().getDiscardForTest().getSize());
    EXPECT_EQ(0, game.getPlayerForTest().getDeckForTest().getSize());

    game.discardAll();

    EXPECT_EQ(RetCode::DeckSuffled, game.draw(5));
    EXPECT_EQ(5, game.getPlayerForTest().getHandForTest().getSize());
    EXPECT_EQ(0, game.getPlayerForTest().getDiscardForTest().getSize());
    EXPECT_EQ(5, game.getPlayerForTest().getDeckForTest().getSize());

    game.discardAll();

}
