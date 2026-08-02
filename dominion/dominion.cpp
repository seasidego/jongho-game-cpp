#include "dominion.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>

void printLine() {
    std::cout << "-------------------" << std::endl;
}

// UTF-8 문자열의 실제 터미널 출력 너비(바이트 크기 아님)를 계산하는 헬퍼 함수
int getVisualWidth(const std::string& str) {
    int width = 0;
    for (size_t i = 0; i < str.length();) {
        unsigned char c = str[i];
        if (c < 0x80) { width += 1; i += 1; }              // 아스키 문자 (1칸)
        else if ((c & 0xE0) == 0xC0) { width += 2; i += 2; } // 2바이트 문자
        else if ((c & 0xF0) == 0xE0) { width += 2; i += 3; } // 3바이트 문자 (한글 등, 2칸)
        else if ((c & 0xF8) == 0xF0) { width += 2; i += 4; } // 4바이트 문자
        else { i += 1; }
    }
    return width;
}

std::string categoryToString(Card::Category cat) {
    switch (cat) {
        case Card::Category::Action:   return "Action";
        case Card::Category::Attack:   return "Attack";
        case Card::Category::Treasure: return "Treasure";
        case Card::Category::Victory:  return "Victory";
        default: return "";
    }
}

// 특정 너비에 맞춰 텍스트와 공백을 조합해주는 함수
std::string padRight(const std::string& str, int targetWidth) {
    int currentWidth = getVisualWidth(str);
    int padding = targetWidth - currentWidth;
    return str + (padding > 0 ? std::string(padding, ' ') : "");
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

void Card::printPretty() const {
    const int cardWidth = 18; // 테두리를 제외한 내부 콘텐츠 너비

    // 1. 카테고리 문자열 합성 (예: "Action - Attack")
    std::string catStr = "";
    for (size_t i = 0; i < categoris_.size(); ++i) {
        catStr += categoryToString(categoris_[i]);
        if (i < categoris_.size() - 1) catStr += " - ";
    }

    // 2. 상단 테두리
    std::cout << "┌──────────────────┐\n";

    // 3. 카드 이름 (좌측 정렬)
    std::cout << std::format("│ {} │\n", padRight(name_, cardWidth));

    // 4. 구분선 1
    std::cout << "├──────────────────┤\n";

    // 5. 비용 및 카테고리 정보 출력
    std::string costStr = std::format("Cost: {}", cost_);
    std::cout << std::format("│ {} │\n", padRight(costStr, cardWidth));
    std::cout << std::format("│ {} │\n", padRight(catStr, cardWidth));

    // 6. 구분선 2 (효과 텍스트 구분을 위한 빈 공간 또는 점선)
    std::cout << "├──────────────────┤\n";

    // 7. 능력(Abilities) 출력 예시 (기본 능력 개수 등에 따라 조정 가능)
    // 여기서는 간단히 보기가 좋도록 빈 칸으로 예시를 들거나 실제 데이터 바인딩 가능
    std::string abilityDemo = "Ability Active";
    std::cout << std::format("│ {} │\n", padRight(abilityDemo, cardWidth));
    std::cout << std::format("│ {} │\n", padRight("", cardWidth)); // 여백

    // 8. 하단 테두리
    std::cout << "└──────────────────┘\n";
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
    // printPretty();
    return;
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

const std::vector<Card::Type>& CardPile::getCardsForTest() const {
    return cards_;
}

std::vector<Card::Type>& CardPile::getCardsForTest() {
    return cards_;
}

void Deck::setStartCard() {
    for (int i = 0; i < 3; i++) {
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
    Card::Type cardType = hand_.takeCard(index);
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

    playGround_.addCard(cardType);
    return cardType;
}

void Player::nextPhase() {
    switch (currentPhase_) {
        case PlayPhase::Action: currentPhase_ = PlayPhase::Buy; break;
        case PlayPhase::Buy: currentPhase_ = PlayPhase::Action; break;
    }
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
    return cards_.at(card);
}

// int CardRegistry::getSize() const {
//     return cards_.size();
// }

void CardRegistry::initCards() {
    cards_.emplace(Card::Type::Copper, Card(Card::Type::Copper, "Copper", 0, {Card::Category::Treasure},
        { {BasicAbility(BasicAbility::Ability::Coin, 1)} }, UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Silver, Card(Card::Type::Silver, "Silver", 3, {Card::Category::Treasure},
        { {BasicAbility(BasicAbility::Ability::Coin, 2)} }, UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Gold, Card(Card::Type::Gold, "Gold", 6, {Card::Category::Treasure},
        { {BasicAbility(BasicAbility::Ability::Coin, 2)} }, UniqueAbility(UniqueAbility::Ability::None)));

    cards_.emplace(Card::Type::Estate, Card(Card::Type::Estate, "Estate", 2, {Card::Category::Victory},
        { {BasicAbility(BasicAbility::Ability::Score, 1)} }, UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Duchy, Card(Card::Type::Duchy, "Duchy", 5, {Card::Category::Victory},
        { {BasicAbility(BasicAbility::Ability::Score, 3)} }, UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Province, Card(Card::Type::Province, "Province", 8, {Card::Category::Victory},
        { {BasicAbility(BasicAbility::Ability::Score, 6)} }, UniqueAbility(UniqueAbility::Ability::None)));

    cards_.emplace(Card::Type::Chapel, Card(Card::Type::Chapel, "Chapel", 2, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::None, 0)} }, UniqueAbility(UniqueAbility::Ability::Chapel)));
    cards_.emplace(Card::Type::Cellar, Card(Card::Type::Cellar, "Cellar", 2, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::Action, 1)} }, UniqueAbility(UniqueAbility::Ability::Cellar)));
    cards_.emplace(Card::Type::Moneylender, Card(Card::Type::Moneylender, "Moneylender", 4, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::None, 0)} }, UniqueAbility(UniqueAbility::Ability::Moneylender)));
    cards_.emplace(Card::Type::Workshop, Card(Card::Type::Workshop, "Workshop", 3, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::None, 0)} }, UniqueAbility(UniqueAbility::Ability::Workshop)));
    cards_.emplace(Card::Type::Merchant, Card(Card::Type::Merchant, "Merchant", 3, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::Action, 1)}, {BasicAbility(BasicAbility::Ability::Cards, 1)} }, UniqueAbility(UniqueAbility::Ability::Merchant)));

    cards_.emplace(Card::Type::Village, Card(Card::Type::Village, "Village", 3, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::Cards, 1)}, {BasicAbility(BasicAbility::Ability::Action, 2)} }, UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Market, Card(Card::Type::Market, "Market", 5, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::Cards, 1)}, {BasicAbility(BasicAbility::Ability::Action, 2)},
            {BasicAbility(BasicAbility::Ability::Buy, 1)}, {BasicAbility(BasicAbility::Ability::Coin, 2)} },
        UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Laboratory, Card(Card::Type::Laboratory, "Laboratory", 5, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::Cards, 2)}, {BasicAbility(BasicAbility::Ability::Action, 1)} }, UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Festival, Card(Card::Type::Festival, "Festival", 5, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::Action, 2)}, {BasicAbility(BasicAbility::Ability::Buy, 1)}, {BasicAbility(BasicAbility::Ability::Coin, 1)} },
        UniqueAbility(UniqueAbility::Ability::None)));
    cards_.emplace(Card::Type::Smithy, Card(Card::Type::Smithy, "Smithy", 3, {Card::Category::Action},
        { {BasicAbility(BasicAbility::Ability::Cards, 3)}}, UniqueAbility(UniqueAbility::Ability::None)));
}

void CardRegistry::print() const{
    for (const auto& r : cards_) {
        r.second.print();
    }
}

int Game::inputBuy() {
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

        if (supply_.isValid(cardInt)) {
            std::cout << "enter number(1~17)" << std::endl;
            continue;
        }
        break;
    }
    return cardInt;
}

RetCode Game::buyCard(int number) {
    Card::Type cardType = supply_.indexToCardType(number);

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
}

RetCode Game::play(int index) {
    Player* _player = getCurPlayer();
    if (_player == nullptr) {
        return RetCode::InvaildPlayer;
    }
    Player& player = *_player;

    auto card = player.play(index, registry_);
    if (card == Card::Type::None) {
        return RetCode::CardNotFound;
    }

    int drawCard = 0;
    for (const auto& a : registry_.getInfo(card).getAbilitys())  {
        auto state = a.getAbilityToTrunState();
        if (state != TurnState::None) {
            player.addState(state, a.getAmount());
        }

        if (a.getAbility() == BasicAbility::Ability::Cards) {
            drawCard = a.getAmount();
        }
    }

    if (drawCard > 0) {
        return draw(drawCard);
    }

    return RetCode::Success;
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
