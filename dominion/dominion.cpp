#include "dominion.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <cassert>
#include <format>

void printLine() {
    std::cout << "-------------------" << std::endl;
}

BasicAbility::Ability BasicAbility::getAbility() const {
    return ability_;
}

TurnState BasicAbility::getAbilityToTrunState() const {
    switch (ability_) {
        case Ability::Action: return TurnState::Action;
        case Ability::Buy: return TurnState::Buy;
        case Ability::Coin: return TurnState::Coin;
        default: return TurnState::None;
    }
}

int BasicAbility::getAmount() const {
    return amount_;
}

UniqueAbility::Ability UniqueAbility::getAbility() const {
    return ability_;
}

int Card::getCost() const{
    return cost_;
}

const std::vector<Card::Category>& Card::getCategorys() const {
    return categoris_;
}

const std::vector<BasicAbility>& Card::getAbilitys() const {
    return abilitys_;
}

void Card::print() const {
    std::cout << "name: " << name_ << std::endl;
    std::cout << "cost: " << cost_ << std::endl;
    std::cout << "abilitys: ";
    for (const auto& a : abilitys_) {
        std::cout << a.getAbility() << " ";
    }
    std::cout << std::endl;
    std::cout << "uniqueAbility: " << uniqueAbility_.getAbility() << std::endl;
    std::cout << "categoris: ";
    for (const auto& c : categoris_) {
        std::cout << c << " ";
    }
    printLine();
}

RetCode Card::play(Player& player, Game& game) const {
    int drawCard = 0;
    for (const auto& a : abilitys_)  {
        auto state = a.getAbilityToTrunState();
        if (state != TurnState::None) {
            player.addState(state, a.getAmount());
        }

        if (a.getAbility() == BasicAbility::Ability::Cards) {
            drawCard = a.getAmount();
        }
    }

    if (drawCard > 0) {
        return player.draw(drawCard);
    }

    return RetCode::Success;
}

RetCode Chapel::play(Player& player, Game& game) const {
    auto retCode = Card::play(player, game);
    if (retCode != RetCode::Success) {
        return retCode;
    }
    player.getHand().print();
    std::cout << std::format("Trash up to {} cards from your hand. >\n", trashCardAmount);
    auto indexes = game.inputHandIndex(trashCardAmount);

    for (const auto index : indexes) {
        if (index == -1) { // dis -1 to change one base to zero base. so it has to be -1
            return RetCode::UserDontWant;
        }
        if (game.trashCardFromHand(index) != RetCode::Success) {
            return RetCode::CardNotFound;
        }
    }

    return RetCode::Success;
}

RetCode Cellar::play(Player& player, Game& game) const {
    auto retCode = Card::play(player, game);
    if (retCode != RetCode::Success) {
        return retCode;
    }
    player.getHand().print();

    int index = 0;
    Card::Type card;
    std::cout << std::format("Discard any number of cards. +1 Card pear card discarded. >\n");
    auto indexes = game.inputHandIndex(player.getHand().getSize());
    int cardDraw = 0;

    for (const auto& i : indexes) {
        player.addCardDiscard(player.takeCardFromHand(i));
        cardDraw++;
    }

    player.draw(cardDraw);
    return RetCode::Success;
}

RetCode Moneylender::play(Player& player, Game& game) const {
    auto retCode = Card::play(player, game);
    if (retCode != RetCode::Success) {
        return retCode;
    }

    player.getHand().print();
    int index = 0;
    Card::Type card;

    while (true) {
        std::cout << std::format("You may trash a Copper from you hand for +{} coins >\n", coinAmount);
        auto indexes = game.inputHandIndex(1);
        if (indexes.size() > 0) {
            index = indexes[0];
            if (index == -1) { // dis -1 to change one base to zero base. so it has to be -1
                return RetCode::UserDontWant;
            }
            if (player.getHand().getCard(index) == Card::Type::Copper) {
                break;
            }
        }
    }

    game.trashCardFromHand(index);
    player.addState(TurnState::Coin, coinAmount);

    return RetCode::Success;
}

RetCode Workshop::play(Player& player, Game& game) const {
    auto retCode = Card::play(player, game);
    if (retCode != RetCode::Success) {
        return retCode;
    }
    std::cout << std::format("Gain a card costing up to {} >\n", maxCost);
    while (true) {
        int index = game.inputGetFromSupply();
        if (index == -1) { // dis -1 to change one base to zero base. so it has to be -1
            return RetCode::UserDontWant;
        }
        if (game.gainCardByCost(index, maxCost) == RetCode::Success) {
            break;
        }
    }
    return RetCode::Success;
}

void CardPile::addCard(Card::Type card) {
    cards_.emplace_back(card);
}

Card::Type CardPile::takeCard(int index) {
    if (index >= 0 && index < cards_.size()) {
        Card::Type card = cards_[index];
        cards_.erase(cards_.begin() + index);
        return card;
    }
    return Card::Type::None;
}

Card::Type CardPile::getCard(int index) const {
    if (index >= 0 && index < cards_.size()) {
        Card::Type card = cards_[index];
        return card;
    }
    return Card::Type::None;
}

void CardPile::print() const {
    std::cout << "CardPile: " << std::endl;
    for (const auto& c : cards_) {
        std::cout << c << std::endl;
    }
    printLine();
}

int CardPile::getSize() const {
    return cards_.size();
}

void CardPile::shuffle() {
    // 1. 하드웨어 시드를 기반으로 난수 생성기 초기화
    std::random_device rd;
    std::mt19937 g(rd());

    // 2. std::shuffle을 이용해 vector 요소들을 무작위로 섞음
    std::shuffle(cards_.begin(), cards_.end(), g);
}

void CardPile::insert(const std::vector<Card::Type>& cards) {
    cards_.insert(cards_.begin() , cards.begin(), cards.end());
}

std::vector<Card::Type> CardPile::takeAllCards() {
    auto cards = cards_;
    cards_.clear();
    return cards;
}

bool CardPile::isValid(int cardIndex) const {
    if (cardIndex >= cards_.size() || cardIndex < 0) {
        return false;
    }
    return true;
}

const std::vector<Card::Type>& CardPile::getCardsForTest() const {
    return cards_;
}

std::vector<Card::Type>& CardPile::getCardsForTest() {
    return cards_;
}

void Deck::setStartCard() {
    for (int i = 0; i < 1; i++) {
        cards_.emplace_back(Card::Type::Estate);
    }
    for (int i = 0; i < 1; i++) {
        cards_.emplace_back(Card::Type::Copper);
    }
    for (int i = 0; i < 1; i++) {
        cards_.emplace_back(Card::Type::Estate);
    }
    for (int i = 0; i < 7; i++) {
        cards_.emplace_back(Card::Type::Copper);
    }
}

void Deck::setStartCardAllVillegeForTest() {
    cards_.clear();
    for (int i = 0; i < 10; i++) {
        cards_.emplace_back(Card::Type::Village);
    }
}

void Deck::print() const {
    std::cout << "Deck: " << std::endl;
    for (const auto& c : cards_) {
        std::cout << c << std::endl;
    }
    printLine();
}

void Hand::print() const {
    std::cout << "Hand: " << std::endl;
    for (const auto& c : cards_) {
        std::cout << c << std::endl;
    }
    printLine();
}

void Discard::print() const {
    std::cout << "Discard: " << std::endl;
    for (const auto& c : cards_) {
        std::cout << c << std::endl;
    }
    printLine();
}

void Trash::print() const {
    std::cout << "Trash: " << std::endl;
    for (const auto& c : cards_) {
        std::cout << c << std::endl;
    }
    printLine();
}

RetCode Supply::discard(Card::Type card) {
    int index = cardTypeToIndex(card);
    if (index == -1) {
        return RetCode::InvaildSupply;
    }
    cards_[index].second -= 1;
    return RetCode::Success;
}

void Supply::printWithIndex() const {
    std::cout << "Supply: " << std::endl;
    int index = 0;
    for (const auto& c : cards_) {
        std::cout << index << ": " << c.first << " : " << c.second << std::endl;
        index++;
    }
    printLine();
}

bool Supply::isValid(int cardNubmer) const {
    if (cardNubmer >= cards_.size() || cardNubmer < 0) {
        return false;
    }
    return true;
}

Card::Type Supply::indexToCardType(int cardIndex) const {
    if (isValid(cardIndex)) {
        return cards_[cardIndex].first;
    }
    return Card::Type::None;
}

int Supply::cardTypeToIndex(Card::Type cardType) const {
    const auto it = std::find_if(cards_.begin(), cards_.end(), [&](const auto& pile) {
        return pile.first == cardType;
    });

    if (it == cards_.end()) {
        return -1;
    }

    return std::distance(cards_.begin(), it);
}

bool Supply::checkCanBuyCard(Card::Type card) const{
    int index = cardTypeToIndex(card);
    if (index == -1) {
        return false;
    }

    if (cards_[index].second <= 0) {
        return false;
    }
    return true;
}

void Supply::print() const {
    std::cout << "Supply: " << std::endl;
    for (const auto& c : cards_) {
        std::cout << c.first << " : " << c.second << std::endl;
    }
    printLine();
}

const std::vector<Supply::Pile>& Supply::getCardsForTest() const {
    return cards_;
}

void Supply::initCards() {
    cards_.emplace_back(Card::Type::Copper, 60);
    cards_.emplace_back(Card::Type::Silver, 40);
    cards_.emplace_back(Card::Type::Gold, 30);
    cards_.emplace_back(Card::Type::Estate, 8);
    cards_.emplace_back(Card::Type::Duchy, 8);
    cards_.emplace_back(Card::Type::Province, 8);

    cards_.emplace_back(Card::Type::Chapel, 10);
    cards_.emplace_back(Card::Type::Cellar, 10);
    cards_.emplace_back(Card::Type::Moneylender, 10);
    cards_.emplace_back(Card::Type::Workshop, 10);
    cards_.emplace_back(Card::Type::Merchant, 10);
    cards_.emplace_back(Card::Type::Village, 10);
    cards_.emplace_back(Card::Type::Market, 10);
    cards_.emplace_back(Card::Type::Laboratory, 10);
    cards_.emplace_back(Card::Type::Festival, 10);
    cards_.emplace_back(Card::Type::Smithy, 10);
}

void PlayGround::print() const {
    std::cout << "PlayGround: " << std::endl;
    for (const auto& c : cards_) {
        std::cout << c << std::endl;
    }
    printLine();
}

void Player::print() const {
    std::cout << "Player" << std::endl;
    printLine();
    deck_.print();
    hand_.print();
    discard_.print();
    playGround_.print();
    std::cout << "States: " << std::endl;
    for (const auto& t : turnState_) {
        std::cout << t.first << " : " << t.second << std::endl;
    }
}

void Player::printHand() const {
    hand_.print();
}

void Player::setStartCard() {
    deck_.setStartCard();
}

int Player::getState(TurnState state) const {
    auto it = turnState_.find(state);
    if (it == turnState_.end()) {
        return 0;
    }
    return it->second;
}

void Player::addCardDiscard(Card::Type card) {
    discard_.addCard(card);
}

void Player::addState(TurnState state, int amount) {
    auto it = turnState_.find(state);
    if (it == turnState_.end()) {
        return;
    }
    it->second += amount;
}

void Player::resetTurnState() {
    turnState_[TurnState::Action] = 1;
    turnState_[TurnState::Buy] = 1;
    turnState_[TurnState::Coin] = 0;
}

RetCode Player::draw(int amount) {
    bool shuffle = false;
    if (discard_.getSize() <= 0 && deck_.getSize() <= 0) {
        return RetCode::EmptyDiscardAndDeck;
    }

    if (discard_.getSize() > 0 && deck_.getSize() == 0) {
        discard_.shuffle();
        deck_.insert(discard_.takeAllCards());
        shuffle = true;
    }

    for (int i = 0; i < amount; i++) {
        hand_.addCard(deck_.takeCard(0));
    }
    if (shuffle) {
        return RetCode::DeckSuffled;
    }
    return RetCode::Success;
}

void Player::discardAll() {
    int size = hand_.getSize();
    for (int i = 0; i < size; i++) {
        discard_.addCard(hand_.takeCard(0)) ;
    }
}

Card::Type Player::play(int index, const CardRegistry& registry) {
    Card::Type cardType = hand_.getCard(index);
    if (cardType == Card::Type::None) {
        return Card::Type::None;
    }

    const auto& category = registry.getInfo(cardType).getCategorys();
    if (currentPhase_ == PlayPhase::Action) {
        if (std::find(category.begin(), category.end(), Card::Category::Action) == category.end() || turnState_.at(TurnState::Action) <= 0) {
            return Card::Type::None;
        }
        addState(TurnState::Action, -1);
    }
    else if (currentPhase_ == PlayPhase::Buy) {
        if (std::find(category.begin(), category.end(), Card::Category::Treasure) == category.end()) {
            return Card::Type::None;
        }
    }

    cardType = hand_.takeCard(index);
    playGround_.addCard(cardType);
    return cardType;
}

void Player::nextPhase() {
    switch (currentPhase_) {
        case PlayPhase::Action: currentPhase_ = PlayPhase::Buy; break;
        case PlayPhase::Buy: currentPhase_ = PlayPhase::Action; break;
    }
}

Card::Type Player::takeCardFromHand(int index) {
    return hand_.takeCard(index);
}

const Hand& Player::getHand() const {
    return hand_;
}

const Hand& Player::getHandForTest() const {
    return hand_;
}

const Deck& Player::getDeckForTest() const {
    return deck_;
}

const Discard& Player::getDiscardForTest() const {
    return discard_;
}

Hand& Player::getHandForTest() {
    return hand_;
}

Deck& Player::getDeckForTest() {
    return deck_;
}

Discard& Player::getDiscardForTest() {
    return discard_;
}

const std::map<TurnState, int>& Player::getTurnStateForTest() const {
    return turnState_;
}

void Player::setStartCardAllVillegeForTest() {
    deck_.setStartCardAllVillegeForTest();
}

const Card& CardRegistry::getInfo(Card::Type card) const {
    return *(cards_.at(card));
}

// int CardRegistry::getSize() const {
//     return cards_.size();
// }

void CardRegistry::initCards() {
    cards_.emplace(
        Card::Type::Copper,
        std::make_unique<Card>(
            Card::Type::Copper, "Copper", 0,
            std::vector<Card::Category>{Card::Category::Treasure},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Coin, 1} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Silver,
        std::make_unique<Card>(
            Card::Type::Silver, "Silver", 3,
            std::vector<Card::Category>{Card::Category::Treasure},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Coin, 2} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Gold,
        std::make_unique<Card>(
            Card::Type::Gold, "Gold", 6,
            std::vector<Card::Category>{Card::Category::Treasure},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Coin, 2} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );

    cards_.emplace(
        Card::Type::Estate,
        std::make_unique<Card>(
            Card::Type::Estate, "Estate", 2,
            std::vector<Card::Category>{Card::Category::Victory},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Score, 1} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Duchy,
        std::make_unique<Card>(
            Card::Type::Duchy, "Duchy", 5,
            std::vector<Card::Category>{Card::Category::Victory},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Score, 3} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Province,
        std::make_unique<Card>(
            Card::Type::Province, "Province", 8,
            std::vector<Card::Category>{Card::Category::Victory},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Score, 6} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );

    cards_.emplace(
        Card::Type::Chapel,
        std::make_unique<Chapel>(
            Card::Type::Chapel, "Chapel", 2,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::None, 0} },
            UniqueAbility(UniqueAbility::Ability::Chapel)
        )
    );
    cards_.emplace(
        Card::Type::Cellar,
        std::make_unique<Cellar>(
            Card::Type::Cellar, "Cellar", 2,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Action, 1} },
            UniqueAbility(UniqueAbility::Ability::Cellar)
        )
    );
    cards_.emplace(
        Card::Type::Moneylender,
        std::make_unique<Moneylender>(
            Card::Type::Moneylender, "Moneylender", 4,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::None, 0} },
            UniqueAbility(UniqueAbility::Ability::Moneylender)
        )
    );
    cards_.emplace(
        Card::Type::Workshop,
        std::make_unique<Workshop>(
            Card::Type::Workshop, "Workshop", 3,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::None, 0} },
            UniqueAbility(UniqueAbility::Ability::Workshop)
        )
    );
    cards_.emplace(
        Card::Type::Merchant,
        std::make_unique<Card>(
            Card::Type::Merchant, "Merchant", 3,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Action, 1}, {BasicAbility::Ability::Cards, 1} },
            UniqueAbility(UniqueAbility::Ability::Merchant)
        )
    );

    cards_.emplace(
        Card::Type::Village,
        std::make_unique<Card>(
            Card::Type::Village, "Village", 3,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Cards, 1}, {BasicAbility::Ability::Action, 2} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Market,
        std::make_unique<Card>(
            Card::Type::Market, "Market", 5,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{
                {BasicAbility::Ability::Cards, 1}, {BasicAbility::Ability::Action, 2},
                {BasicAbility::Ability::Buy, 1}, {BasicAbility::Ability::Coin, 2}
            },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Laboratory,
        std::make_unique<Card>(
            Card::Type::Laboratory, "Laboratory", 5,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Cards, 2}, {BasicAbility::Ability::Action, 1} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Festival,
        std::make_unique<Card>(
            Card::Type::Festival, "Festival", 5,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Action, 2}, {BasicAbility::Ability::Buy, 1}, {BasicAbility::Ability::Coin, 1} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
    cards_.emplace(
        Card::Type::Smithy,
        std::make_unique<Card>(
            Card::Type::Smithy, "Smithy", 3,
            std::vector<Card::Category>{Card::Category::Action},
            std::vector<BasicAbility>{ {BasicAbility::Ability::Cards, 3} },
            UniqueAbility(UniqueAbility::Ability::None)
        )
    );
}

void CardRegistry::print() const{
    for (const auto& r : cards_) {
        r.second->print();
    }
}

int Game::inputGetFromSupply() {
    if (isTest_) {
        assert(supply_.isValid(inputBuyTest_));
        return inputBuyTest_;
    }
    std::string cardNumber;
    int cardInt = 0;
    supply_.printWithIndex();
    std::cout << "enter number" << std::endl;
    while (true) {
        std::cin >> cardNumber;
        try {
            cardInt = std::stoi(cardNumber);
        }
        catch (const std::invalid_argument& e) {
            std::cout << "enter number" << std::endl;
            continue;
        }

        cardInt--;  // user input int is 1 base. card pile is zero base.
        if (!supply_.isValid(cardInt)) {
            std::cout << "enter number(1~17)" << std::endl;
            continue;
        }
        break;
    }
    return cardInt;
}

RetCode Game::buyCard(int index) {
    Card::Type cardType = supply_.indexToCardType(index);

    Player* _player = getCurPlayer();
    if (_player == nullptr) {
        return RetCode::InvaildPlayer;
    }

    Player& player = *_player;

    int cost = registry_.getInfo(cardType).getCost();

    if (!supply_.checkCanBuyCard(cardType)) {
        return RetCode::EmptySupply;
    }

    if (player.getState(TurnState::Coin) < cost) {
        return RetCode::NoEnoughCoin;
    }

    if (player.getState(TurnState::Buy) < 1) {
        return RetCode::NoEnoughBuy;
    }

    player.addState(TurnState::Coin, -cost);
    player.addState(TurnState::Buy, -1);
    player.addCardDiscard(cardType);
    supply_.discard(cardType);

    return RetCode::Success;
}

RetCode Game::gainCardByCost(int index, int maxCost) {
    Card::Type cardType = supply_.indexToCardType(index);

    Player* _player = getCurPlayer();
    if (_player == nullptr) {
        return RetCode::InvaildPlayer;
    }

    Player& player = *_player;

    int cost = registry_.getInfo(cardType).getCost();

    if (!supply_.checkCanBuyCard(cardType)) {
        return RetCode::EmptySupply;
    }

    if (maxCost < cost) {
        return RetCode::NoEnoughCoin;
    }

    player.addCardDiscard(cardType);
    supply_.discard(cardType);

    return RetCode::Success;
}

void Game::setStartCard() {
    for (auto& p : players_) {
        p.setStartCard();
    }
}

void Game::resetTurnState() {
    for (auto& p : players_) {
        p.resetTurnState();
    }
}

void Game::initRegistry() {
    registry_.initCards();
}

void Game::initSupply() {
    supply_.initCards();
}

void Game::print() const {
    std::cout << "Game: " << std::endl;
    printLine();
    supply_.print();
    trash_.print();
    for (const auto& p : players_) {
        p.print();
    }
    // registry_.print();
}

void Game::addPlayer() {
    players_.emplace_back(Player());
}

const Supply& Game::getSupplyForTest() const {
    return supply_;
}

RetCode Game::draw(int amount) {
    Player* player = getCurPlayer();
    if (player == nullptr) {
        return RetCode::InvaildPlayer;
    }

    RetCode ret = player->draw(amount);

    if (ret == RetCode::EmptyDiscardAndDeck) {
        return RetCode::EmptyDiscardAndDeck;
    }
    else if (ret == RetCode::DeckSuffled) {
        return RetCode::DeckSuffled;
    }
    return RetCode::Success;
}

Player* Game::getCurPlayer() {
    if (playerTurn_ > players_.size() && playerTurn_ < 0) {
        return nullptr;
    }

    return &players_.at(playerTurn_);
}

const Player* Game::getCurPlayer() const{
    if (playerTurn_ > players_.size() && playerTurn_ < 0) {
        return nullptr;
    }

    return &players_.at(playerTurn_);
}

RetCode Game::discardAll() {
    Player* player = getCurPlayer();
    if (player == nullptr) {
        return RetCode::InvaildPlayer;
    }

    player->discardAll();

    return RetCode::Success;
}

void Game::init() {
    addPlayer();
    initRegistry();
    initSupply();
    setStartCard();
    resetTurnState();
}

const Player& Game::getPlayerForTest() const{
    return players_.at(playerTurn_);
}

Player& Game::getPlayerForTest() {
    return players_.at(playerTurn_);
}

RetCode Game::setStartCardAllVillegeForTest() {
    Player* player = getCurPlayer();
    if (player == nullptr) {
        return RetCode::InvaildPlayer;
    }

    player->setStartCardAllVillegeForTest();
    return RetCode::Success;
}

RetCode Game::play(int index) {
    Player* _player = getCurPlayer();
    if (_player == nullptr) {
        return RetCode::InvaildPlayer;
    }
    Player& player = *_player;

    auto cardType = player.play(index, registry_);
    if (cardType == Card::Type::None) {
        return RetCode::CardNotFound;
    }

    const auto& card = registry_.getInfo(cardType);

    return card.play(player, *this);
}

RetCode Game::nextPhase() {
    Player* _player = getCurPlayer();
    if (_player == nullptr) {
        return RetCode::InvaildPlayer;
    }
    Player& player = *_player;

    player.nextPhase();
    return RetCode::Success;

}

std::vector<std::string> Game::splitString(std::string s) {
     std::stringstream ss(s);
     std::string word;
     std::vector<std::string> words;
     int numberInt = 0;

    while (std::getline(ss, word, ',')) {
         words.push_back(word);
    }

    return words;
 }

std::vector<int> Game::inputHandIndex(int amount) const {
    if (isTest_) {
        // if indexes is not sorted, and when index 1 is trashed and index 3 need to trashed,
        // index 3 will not be the index 3 in first cardpile
        auto inputTest = inputTest_;
        std::sort(inputTest.begin(), inputTest.end(), [](const auto& a, const auto& b){
            return a > b;
        });

        assert(inputTest.size() <= amount);
        auto it = std::adjacent_find(inputTest.begin(), inputTest.end());
        assert(it == inputTest.end());

        return inputTest;
    }

    std::string select;
    std::vector<int> selectedInt;

    const Player* _player = getCurPlayer();
    if (_player == nullptr) {
        return {};
    }
    const Player& player = *_player;

    std::cout << "select indexes of the cards. if you want to stop selecting, enter 0 and press enter" << std::endl;
    bool wrong = false;
    while (true) {
        selectedInt.clear();
        wrong = false;
        std::cin >> select;
        std::vector<std::string> numbers = splitString(select);

        for (const auto& n : numbers) {
            int number = 0;
            try {
                 number = std::stoi(n);
                 number--;
            }
            catch (const std::invalid_argument& e) {
                std::cout << "enter number" << std::endl;
                wrong = true;
                break;
            }
            if (number > player.getHand().getSize()) {
                std::cout << "input went wrong. you can only use 1 ~ " << player.getHand().getSize() << std::endl;
                wrong = true;
                break;
            }
            if (std::find(selectedInt.begin(), selectedInt.end(), number) != selectedInt.end()) {
                std::cout << "you can't input same number" << std::endl;
                wrong = true;
                break;
            }
            selectedInt.emplace_back(number);
        }

        if (!wrong) {
            break;
        }
    }
    // if indexes is not sorted, and when index 1 is trashed and index 3 need to trashed,
    // index 3 will not be the index 3 in first cardpile
    std::sort(selectedInt.begin(), selectedInt.end(), [](const auto& a, const auto& b){
        return a > b;
    });
    return selectedInt;
}

RetCode Game::trashCardFromHand(int index) {
    Player* player = getCurPlayer();
    if (player == nullptr) {
        return RetCode::InvaildPlayer;
    }
    Card::Type cardType = player->takeCardFromHand(index);
    if (cardType == Card::Type::None) {
        return RetCode::CardNotFound;
    }

    trash_.addCard(cardType);
    return RetCode::Success;
}

void Game::setTestInput(const std::vector<int>& indexes) {
    for (const auto& i : indexes) {
        inputTest_.emplace_back(i - 1);
    }

    isTest_ = true;
}

void Game::setTestBuyInput(int index) {
    inputBuyTest_ = index - 1;
    isTest_ = true;
}
