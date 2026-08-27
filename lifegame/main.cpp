#include <iostream>
#include <format>
#include "lifegame.h"
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

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

    Grid grid;

    if (argc >= 2) {
        if (std::strcmp(argv[1], "random") == 0) {
            grid.initGridRandom(50);
        } else if (std::strcmp(argv[1], "cross") == 0) {
            // cross
            grid.initGrid(50);
            grid.setAlive(5, 4);
            grid.setAlive(5, 5);
            grid.setAlive(5, 6);
            grid.setAlive(4, 5);
            grid.setAlive(5, 5);
            grid.setAlive(6, 5);
        } else if (std::strcmp(argv[1], "glider") == 0) {
            // glider
            grid.initGrid(50);
            grid.setAlive(3, 3);
            grid.setAlive(3, 4);
            grid.setAlive(3, 5);
            grid.setAlive(2, 5);
            grid.setAlive(1, 4);
        } else if (std::strcmp(argv[1], "gun") == 0) {
            grid.initSpaceGliderGun();
        }
    } else {
        grid.initGrid(50);
        grid.setAlive(3, 11);
        grid.setAlive(4, 11);
        grid.setAlive(5, 10); grid.setAlive(5, 11); grid.setAlive(5, 12);

        grid.setAlive(8, 10); grid.setAlive(8, 11); grid.setAlive(8, 12);
        grid.setAlive(9, 11);
        grid.setAlive(10, 11);
        grid.setAlive(11, 11);
        grid.setAlive(12, 11);
        grid.setAlive(13, 10); grid.setAlive(13, 11); grid.setAlive(13, 12);

        grid.setAlive(16, 10); grid.setAlive(16, 11); grid.setAlive(16, 12);
        grid.setAlive(17, 11);
        grid.setAlive(18, 11);
        
    }
    
    grid.print();
    std::this_thread::sleep_for(std::chrono::seconds(2));

    while (true) {
        grid.start();
        grid.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
