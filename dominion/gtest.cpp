#include <gtest/gtest.h>
#include "dominion.h"

TEST(Dominion, addNumber) {
    EXPECT_EQ(3, 1 + 2);
}

TEST(Dominion, Buy) {
    Game game;
    game.init();

    game.buyCard(0);
    EXPECT_EQ(59, game.getSupplyForTest().getCardsForTest().at(0).second);
    EXPECT_EQ(RetCode::NoEnoughBuy, game.buyCard(0));

    // game.print();
    // std::cout << "end" << std::endl;
}

TEST(Dominion, DrawAndDiscard) {
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

TEST(Dominion, play) {
    Game game;
    game.init();

    EXPECT_EQ(RetCode::Success, game.draw(5));
    EXPECT_EQ(Card::Type::Copper, game.getPlayerForTest().getHandForTest().getCardsForTest().at(3));
    EXPECT_EQ(RetCode::Success, game.nextPhase());
    EXPECT_EQ(RetCode::Success, game.play(3));
    EXPECT_EQ(1, game.getPlayerForTest().getTurnStateForTest().at(TurnState::Coin));
}

TEST(Dominion, playActionCard) {
    Game game;
    game.init();
    game.setStartCardAllVillegeForTest();
    Player& player = game.getPlayerForTest();
    EXPECT_EQ(RetCode::Success, game.draw(5));
    auto& deckCard = player.getDeckForTest().getCardsForTest();
    deckCard.emplace(deckCard.begin(), Card::Type::Smithy);

    EXPECT_EQ(6, game.getPlayerForTest().getDeckForTest().getSize());
    EXPECT_EQ(Card::Type::Smithy, game.getPlayerForTest().getDeckForTest().getCardsForTest().at(0));
    EXPECT_EQ(Card::Type::Village, game.getPlayerForTest().getHandForTest().getCardsForTest().at(0));

    // play village: +1card +2action
    game.play(0);
    EXPECT_EQ(5, player.getHandForTest().getSize());
    EXPECT_EQ(2, player.getTurnStateForTest().at(TurnState::Action));

    EXPECT_EQ(Card::Type::Smithy, game.getPlayerForTest().getHandForTest().getCardsForTest().at(4));

    // play smithy: +3card
    EXPECT_EQ(RetCode::Success, game.play(4));
    EXPECT_EQ(7, player.getHandForTest().getSize());
    EXPECT_EQ(1, player.getTurnStateForTest().at(TurnState::Action));
}


TEST(Dominion, playUniqueActionCard) {
    Game game;
    game.init();

    Player& player = game.getPlayerForTest();
    auto& deckCard = player.getDeckForTest().getCardsForTest();
    deckCard.emplace(deckCard.begin(), Card::Type::Chapel);
    EXPECT_EQ(Card::Type::Chapel, game.getPlayerForTest().getDeckForTest().getCardsForTest().at(0));
    EXPECT_EQ(RetCode::Success, game.draw(5));
    game.setTestInput({1, 2});
    game.play(0);

    EXPECT_EQ(2, player.getHandForTest().getSize());
}
