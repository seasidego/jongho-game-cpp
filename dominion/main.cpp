#include <iostream>
#include <format>
#include "dominion.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    for (int i = 0; i < argc ; i++) {
        // 실행할 때 arg에 gtest가 있으면
        if (std::strcmp(argv[i], "gtest") == 0) {
            // google test에 argc, arg 전달
            ::testing::InitGoogleTest(&argc, argv);

            // 여기서 모든 테스트 실행
            return RUN_ALL_TESTS();
        }
    }

    Game game;
    game.init();

    while (true) {
        game.draw(5);

        while (true) {
            auto ret = game.inputPlayCard();
            game.coutRetCode(ret);
            if (ret == RetCode::UserStopPhase) {
                break;
            }
            game.printState();
        }
        game.nextPhase();

        while (true) {
            auto ret = game.inputPlayCard();
            game.coutRetCode(ret);
            if (ret == RetCode::EndPlayTreasure) {
                break;
            }
            game.printState();
        }

        while (true) {
            auto ret = game.inputBuyCard();
            game.coutRetCode(ret);
            if (ret == RetCode::UserStopPhase) {
                break;
            }
        }
        game.discardAll();
        game.resetTurnState();
        game.nextPhase();
        game.clearInThisTurnAbility();
        game.addTurnNumber();

        if (game.checkIsOver()) {
            break;
        }

    }
    

    return 0;
}
