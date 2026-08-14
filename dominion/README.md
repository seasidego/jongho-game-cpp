# Dominion

# 🃏 Dominion Game in C++

A C++ implementation of the popular deck-building board game, **Dominion**. This project focuses on demonstrating clean object-oriented architecture, modular game design, and iterative code refactoring as a C++ student explorer.

---

## 🚀 Key Features

- **Turn-Based Game Loop**: Full implementation of the core phases (Action, Buy, and DiscardAll).
- **Dynamic Deck Management**: Automated handling of drawing, discarding, and reshuffling using pseudo-random generators (`std::mt19937`).
- **Polymorphic Card System**: An extensible base class structure that allows easily adding unique Kingdom card behaviors.

---

## 🏛️ Code Evolution & Architecture

One of the major learning milestones in this project was moving from naive, prototype-level code to an engineered codebase.

### 🔄 Refactoring Highlights

| Feature | From (Initial Naive Code) | To (Refactored & Optimized) |
| :--- | :--- | :--- |
| **Card Architecture & Polymorphism** | Retrieved card types from a registry and used a bulky **`switch-case`** statement to trigger specific abilities. | Stored card data in a registry using **`std::unique_ptr`**, and designed inherited card classes so that calling a single **`.play()`** method executes each card's unique behavior polymorphically. |
| **Card Mechanics** | Massively long **`swich case` chains** to handle different card behaviors. | Implemented **Polymorphism** and derived classes for clean, modular actions. |
| **Game State Control** | Complex boolean flags that made phase transitions hard to track. | Designed a robust **State Machine** pattern to manage turn transitions safely. |
| **Error Management** | Scattered **`std::cout`** statements inside individual functions to print error messages directly. | Centralized error handling by implementing a unified **`enum class ReturnCode`**, separating system logic from the presentation layer. |
---

## 🧠 What I Learned

### 💻 Modern C++ & Memory Safety
- Mastered C++ STL containers (`std::vector`, `std::map`) to model shifting card piles.
- Deepened understanding of object ownership, reference passing, and resource management.

### 📐 Software Design Patterns
- Realized the importance of scalability; designing the structure beforehand saved significant development time during late-game additions.
- Learned how to apply OOP principles (Inheritance, Encapsulation, Polymorphism) to solve real-world logic problems.

---

## 🛠️ Tech Stack & Environment

- **Language:** C++17
- **Build System:** CMake
- **Compiler:** GCC / Clang

## 🗺️ Development Roadmap

- [x] **Core Architecture**: Design the base abstract `Card` class.
- [x] **Collection Management**: Create a robust `Cards` container layer.
- [x] **Inheritance System**: Extend the `Cards` container into specific context piles (`Deck`, `Hand`, `Discard`, and `Supply`).
- [x] **Basic Mechanics**: Implement standard card triggers (`+Action`, `+Draw`, `+Coin`, `+Buy`).
- [x] **Complex Card Logic**: Implement dynamic card side-effects (e.g., interactive discarding, trashing).

---

## 🃏 Game Cards Specifications

| Type | Card Name | Cost | Core & Unique Abilities |
| :---: | :--- | :---: | :--- |
| <br>**💰<br>Treasure** | **Copper** | `0` | 🟡 +1 Coin |
| | **Silver** | `3` | 🟡 +2 Coin |
| | **Gold** | `6` | 🟡 +3 Coin |
| <br>**👑<br>Victory** | **Estate** | `2` | 🟢 +1 Victory Point |
| | **Duchy** | `5` | 🟢 +3 Victory Point |
| | **Province** | `8` | 🟢 +6 Victory Point |
| <br>**⚡<br>Action**<br>*(Simple)* | **Village** | `3` | 🃏 +1 Card / ⚙️ +2 Actions |
| | **Market** | `5` | 🃏 +1 Card / ⚙️ +1 Action / 🟡 +1 Coin / 🛒 +1 Buy |
| | **Laboratory** | `5` | 🃏 +2 Cards / ⚙️ +1 Action |
| | **Festival** | `5` | ⚙️ +2 Actions / 🛒 +1 Buy / 🟡 +2 Coin |
| | **Smithy** | `4` | 🃏 +3 Cards |
| <br>**🔮<br>Action**<br>*(Unique)* | **Chapel** | `2` | 🗑️ Trash up to 4 cards from your hand. |
| | **Cellar** | `2` | ⚙️ +1 Action <br>🔄 Discard any number of cards; draw +1 Card per discarded card. |
| | **Moneylender** | `4` | 🗑️ You may trash a Copper from your hand for 🟡 +3 Coin. |
| | **Workshop** | `3` | 🛒 Gain a card costing up to `4`. |
| | **Merchant** | `3` | 🃏 +1 Card / ⚙️ +1 Action <br>⭐ The first time you play a Silver this turn: 🟡 +1 Coin. |

## 🤖 AI-Assisted Learning

### 🎲 Random Number Generation (`std::mt19937`)


### 🔍 Linear Search (`std::find`)

### 🗑️ Conditional Deletion (`std::erase_if`)
