#include <iostream>
#include <format>
#include "lifegame.h"
#include <gtest/gtest.h>

int main(int argc, char **argv) {
    for (int i = 0; i < argc ; i++) {
        // when start, if arg has gtest
        if (std::strcmp(argv[i], "gtest") == 0) {
            // send argc, arg to google test
            ::testing::InitGoogleTest(&argc, argv);

            // do all tests in here
            return RUN_ALL_TESTS();
        }
    }

    std::cout << "works~" << std::endl;
    return 0;
}
