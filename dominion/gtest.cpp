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


TEST(Dominion, playCellar) {
    Game game;
    game.init();

    Player& player = game.getPlayerForTest();
    auto& deckCard = player.getDeckForTest().getCardsForTest();
    auto& hand = player.getHandForTest();
    auto& handCard = hand.getCardsForTest();
    deckCard.clear();
    deckCard.insert(deckCard.end(), {Card::Type::Cellar, Card::Type::Chapel});
    deckCard.insert(deckCard.end(), {Card::Type::Copper, Card::Type::Silver, Card::Type::Gold});
    deckCard.insert(deckCard.end(), {Card::Type::Village, Card::Type::Smithy});
    deckCard.insert(deckCard.end(), {Card::Type::Estate, Card::Type::Duchy, Card::Type::Province});

    EXPECT_EQ(RetCode::Success, game.draw(5));

    game.setTestInput({1, 2});
    EXPECT_EQ(Card::Type::Cellar, handCard.at(0));
    game.play(0);

    game.print();
    EXPECT_EQ(4, hand.getSize()) << "play cellar : -1, discard : -2, draw : +2 = 4";

    EXPECT_EQ((std::vector<Card::Type>{Card::Type::Silver, Card::Type::Gold, Card::Type::Village, Card::Type::Smithy}), handCard) << "deck's or hand's card is not match";
}

TEST(Dominion, playChapel) {
    Game game;
    game.init();

    Player& player = game.getPlayerForTest();
    auto& deckCard = player.getDeckForTest().getCardsForTest();
    auto& hand = player.getHandForTest();
    auto& handCard = hand.getCardsForTest();
    deckCard.clear();
    deckCard.insert(deckCard.end(), {Card::Type::Chapel, Card::Type::Cellar});
    deckCard.insert(deckCard.end(), {Card::Type::Copper, Card::Type::Silver, Card::Type::Gold});
    deckCard.insert(deckCard.end(), {Card::Type::Village, Card::Type::Smithy});
    deckCard.insert(deckCard.end(), {Card::Type::Estate, Card::Type::Duchy, Card::Type::Province});

    EXPECT_EQ(RetCode::Success, game.draw(5));

    game.setTestInput({1, 2});
    EXPECT_EQ(Card::Type::Chapel, handCard.at(0));
    game.play(0);

    game.print();

    EXPECT_EQ(2, hand.getSize()) << "play chapel : -1, trash : -2";

    EXPECT_EQ((std::vector<Card::Type>{Card::Type::Silver, Card::Type::Gold}), handCard) << "hand's card is not match";
}

TEST(Dominion, playMoneylender) {
    Game game;
    game.init();

    Player& player = game.getPlayerForTest();
    auto& deckCard = player.getDeckForTest().getCardsForTest();
    auto& hand = player.getHandForTest();
    auto& handCard = hand.getCardsForTest();
    deckCard.clear();
    deckCard.insert(deckCard.end(), {Card::Type::Moneylender, Card::Type::Estate});
    deckCard.insert(deckCard.end(), {Card::Type::Copper, Card::Type::Silver, Card::Type::Gold});

    EXPECT_EQ(RetCode::Success, game.draw(5));

    game.setTestInput({2});
    EXPECT_EQ(Card::Type::Moneylender, handCard.at(0));
    game.play(0);

    game.print();

    EXPECT_EQ(3, player.getState(TurnState::Coin));
}

TEST(Dominion, playWorkshop) {
    Game game;
    game.init();
    Player& player = game.getPlayerForTest();
    auto& deckCard = player.getDeckForTest().getCardsForTest();
    auto& hand = player.getHandForTest();
    auto& handCard = hand.getCardsForTest();
    deckCard.clear();
    deckCard.insert(deckCard.end(), {Card::Type::Workshop, Card::Type::Estate});
    deckCard.insert(deckCard.end(), {Card::Type::Copper, Card::Type::Silver, Card::Type::Gold});

    EXPECT_EQ(RetCode::Success, game.draw(5));

    game.setTestBuyInput(9);
    EXPECT_EQ(Card::Type::Workshop, handCard.at(0));
    EXPECT_EQ(RetCode::Success, game.play(0));

    game.print();

    EXPECT_EQ(Card::Type::Moneylender, player.getDiscardForTest().getCardsForTest().at(0));
}
