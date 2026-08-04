#include <iostream>
#include <memory>
#include <sys/stat.h>
#include <utility>
#include <vector>
#include <map>
#include <random>
#include <set>
#include <gtest/gtest_prod.h> // 1. 프로덕션 헤더에 이 gtest 제품용 헤더를 추가합니다.

enum class TurnState {
    None,
    Coin,
    Buy,
    Action,
};

enum class RetCode {
    Success,
    NoEnoughBuy,
    NoEnoughCoin,
    EmptyDeck,
    EmptySupply,
    EmptyHand,
    EmptyDiscard,
    EmptyDiscardAndDeck,
    InvaildPlayer,
    InvaildSupply,
    InvaildState,
    DeckSuffled,
    CardNotFound,
    UserDontWant,
};

class BasicAbility {
public:
    enum class Ability {
        None,
        Action,
        Cards,
        Coin,
        Buy,
        Score,
    };
    BasicAbility(Ability ability, int amount) : ability_(ability), amount_(amount) {};
    Ability getAbility() const;
    TurnState getAbilityToTrunState() const;
    int getAmount() const;
private:
    Ability ability_ = Ability::None;
    int amount_ = 0;
};

class UniqueAbility {
public:
    enum class Ability {
        None,
        Chapel,
        Cellar,
        Moneylender,
        Workshop,
        Merchant,
    };
    UniqueAbility(Ability ability) : ability_(ability) {};
    Ability getAbility() const;
private:
    Ability ability_ = Ability::None;
};

class Player;
class Game;

class Card {
public:
    enum class Category {
        None,
        Action,
        Attack,
        Treasure,
        Victory,
    };
    enum class Type {
        None = 0,
        Copper = 1,
        Silver = 2,
        Gold = 3,
        Estate = 4,
        Duchy = 5,
        Province = 6,
        Chapel = 7,
        Cellar = 8,
        Moneylender = 9,
        Workshop = 10,
        Merchant = 11,
        Village = 12,
        Market = 13,
        Laboratory = 14,
        Festival = 15,
        Smithy = 16
    };

    Card(Type type, std::string name, int cost, std::vector<Category> categoris, std::vector<BasicAbility> abilitys, UniqueAbility uniqueAbility) :
        type_(type), name_(name), cost_(cost), abilitys_(abilitys), uniqueAbility_(uniqueAbility), categoris_(categoris) {};
    int getCost() const;
    const std::vector<Category>& getCategorys() const;
    const std::vector<BasicAbility>& getAbilitys() const;
    void print() const;
    void printPretty() const;

    virtual RetCode play(Player& player, Game& game) const;

private:
    Type type_;
    std::string name_;
    int cost_ = 0;
    std::vector<BasicAbility> abilitys_;
    UniqueAbility uniqueAbility_;
    std::vector<Category> categoris_;
};

class Chapel : public Card {
public:
    Chapel(Type type, std::string name, int cost, std::vector<Category> categoris, std::vector<BasicAbility> abilitys, UniqueAbility uniqueAbility)
    : Card(type, name, cost, categoris, abilitys, uniqueAbility) {};

    RetCode play(Player& player, Game& game) const override;
private:
};

class Cellar : public Card {
public:
    Cellar(Type type, std::string name, int cost, std::vector<Category> categoris, std::vector<BasicAbility> abilitys, UniqueAbility uniqueAbility)
    : Card(type, name, cost, categoris, abilitys, uniqueAbility) {};

    RetCode play(Player& player, Game& game) const override;
private:
};

class CardPile {
public:
    void addCard(Card::Type card);
    Card::Type takeCard(int index);
    int getSize() const;
    virtual void print() const;
    void shuffle();
    void insert(const std::vector<Card::Type>& cards);
    std::vector<Card::Type> takeAllCards();
    bool isValid(int cardIndex) const;

public: // for test
    const std::vector<Card::Type>& getCardsForTest() const;
    std::vector<Card::Type>& getCardsForTest();

protected:
    std::vector<Card::Type> cards_;
};

class Supply {
public:
    using Pile = std::pair<Card::Type, int>;
    void initCards();
    bool checkCanBuyCard(Card::Type card) const;
    RetCode discard(Card::Type card);
    void print() const;
    void printWithIndex() const;
    bool isValid(int cardNubmer) const;
    Card::Type indexToCardType(int cardIndex) const;
    int cardTypeToIndex(Card::Type cardType) const;

public: // for test
    const std::vector<Pile>& getCardsForTest() const;

private:
    std::vector<Pile> cards_;
};

class Hand : public CardPile {
public:
    void print() const override;
private:
};

class Discard : public CardPile {
public:
    void print() const override;

private:
};

class Trash : public CardPile {
public:
    void print() const override;

private:
};

class Deck : public CardPile {
public:
    void setStartCard();
    void print() const override;

public:
    void setStartCardAllVillegeForTest();
private:
};

class PlayGround : public CardPile {
public:
    void print() const override;
private:
};

class CardRegistry;

class Player {
public:
    enum class PlayPhase {
        Action,
        Buy,
    };

    void setStartCard();
    int getState(TurnState state) const;
    void resetTurnState();
    void addCardDiscard(Card::Type card);
    void addState(TurnState state, int amount);
    void print() const;
    void printHand() const;
    RetCode draw(int amount);
    void discardAll();
    Card::Type play(int index, const CardRegistry& registry);
    void nextPhase();
    Card::Type takeCardFromHand(int index);
    const Hand& getHand() const;

public:
    const Hand& getHandForTest() const;
    const Deck& getDeckForTest() const;
    const Discard& getDiscardForTest() const ;
    Hand& getHandForTest();
    Deck& getDeckForTest();
    Discard& getDiscardForTest();
    const std::map<TurnState, int>& getTurnStateForTest() const;
    void setStartCardAllVillegeForTest();

private:
    PlayGround playGround_;
    Deck deck_;
    Hand hand_;
    Discard discard_;
    std::map<TurnState, int> turnState_;
    PlayPhase currentPhase_;
};

class CardRegistry {
public:
    const Card& getInfo(Card::Type card) const;
    void initCards();
    void print() const;
    bool isVaild(int number) const;
private:
    // std::map<Card::Type, Card> cards_;
    std::map<Card::Type, std::unique_ptr<Card>> cards_;
};

class Game {
public:
    static std::vector<std::string> splitString(std::string s);
    int inputBuy();
    RetCode buyCard(int number);
    void resetTurnState();
    void print() const;
    void init();
    RetCode draw(int amount);
    RetCode discardAll();
    RetCode play(int index);
    RetCode nextPhase();
    RetCode trashCardFromHand(int index);
    std::vector<int> inputHandIndex(int amount) const;


private:
    void setStartCard();
    void initSupply();
    void initRegistry();
    void addPlayer();
    Player* getCurPlayer();
    const Player* getCurPlayer() const;

public: // for test
    const Supply& getSupplyForTest() const;
    const Player& getPlayerForTest() const;
    Player& getPlayerForTest();
    RetCode setStartCardAllVillegeForTest();

private:
    Trash trash_;
    Supply supply_;
    std::vector<Player> players_;
    int playerTurn_ = 0;
    CardRegistry registry_;
};

inline std::ostream& operator<<(std::ostream& os, const Card::Type& type) {
    switch (type) {
        case Card::Type::None: os << "None"; break;
        case Card::Type::Copper: os << "Copper"; break;
        case Card::Type::Silver: os << "Silver"; break;
        case Card::Type::Gold: os << "Gold"; break;
        case Card::Type::Estate: os << "Estate"; break;
        case Card::Type::Duchy: os << "Duchy"; break;
        case Card::Type::Province: os << "Province"; break;
        case Card::Type::Chapel: os << "Chapel"; break;
        case Card::Type::Cellar: os << "Cellar"; break;
        case Card::Type::Moneylender: os << "Moneylender"; break;
        case Card::Type::Workshop: os << "Workshop"; break;
        case Card::Type::Merchant: os << "Merchant"; break;
        case Card::Type::Village: os << "Village"; break;
        case Card::Type::Market: os << "Market"; break;
        case Card::Type::Laboratory: os << "Laboratory"; break;
        case Card::Type::Festival: os << "Festival"; break;
        case Card::Type::Smithy: os << "Smithy"; break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const Card::Category& type) {
    switch (type) {
        case Card::Category::None: os << "None"; break;
        case Card::Category::Action: os << "Action"; break;
        case Card::Category::Attack: os << "Attack"; break;
        case Card::Category::Treasure: os << "Treasure"; break;
        case Card::Category::Victory: os << "Victory"; break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const UniqueAbility::Ability& ability) {
    switch (ability) {
        case UniqueAbility::Ability::None: os << "None"; break;
        case UniqueAbility::Ability::Chapel: os << "Chapel"; break;
        case UniqueAbility::Ability::Cellar: os << "Cellar"; break;
        case UniqueAbility::Ability::Moneylender: os << "Moneylender"; break;
        case UniqueAbility::Ability::Workshop: os << "Workshop"; break;
        case UniqueAbility::Ability::Merchant: os << "Merchant"; break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const BasicAbility::Ability& ability) {
    switch (ability) {
        case BasicAbility::Ability::None: os << "None"; break;
        case BasicAbility::Ability::Action: os << "Action"; break;
        case BasicAbility::Ability::Cards: os << "Cards"; break;
        case BasicAbility::Ability::Coin: os << "Coin"; break;
        case BasicAbility::Ability::Buy: os << "Buy"; break;
        case BasicAbility::Ability::Score: os << "Score"; break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const TurnState& state) {
    switch (state) {
        case TurnState::None: os << "None"; break;
        case TurnState::Coin: os << "Coin"; break;
        case TurnState::Buy: os << "Buy"; break;
        case TurnState::Action: os << "Action"; break;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, RetCode code) {
    switch (code) {
        case RetCode::Success:              os << "Success"; break;
        case RetCode::NoEnoughBuy:          os << "NoEnoughBuy"; break;
        case RetCode::NoEnoughCoin:         os << "NoEnoughCoin"; break;
        case RetCode::EmptyDeck:            os << "EmptyDeck"; break;
        case RetCode::EmptySupply:          os << "EmptySupply"; break;
        case RetCode::EmptyHand:            os << "EmptyHand"; break;
        case RetCode::EmptyDiscard:         os << "EmptyDiscard"; break;
        case RetCode::EmptyDiscardAndDeck:  os << "EmptyDiscardAndDeck"; break;
        case RetCode::InvaildPlayer:        os << "InvaildPlayer"; break;
        case RetCode::InvaildSupply:        os << "InvaildSupply"; break;
        case RetCode::InvaildState:         os << "InvaildState"; break;
        case RetCode::DeckSuffled:          os << "DeckSuffled"; break;
        default:                            os << "UnknownRetCode"; break;
    }
    return os;
}
