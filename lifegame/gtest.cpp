#include <gtest/gtest.h>
#include "lifegame.h"

TEST(lifegame, addNumber) {
    Grid grid;
    grid.initGrid();
    
    grid.setAlive(5, 4);
    grid.setAlive(5, 5);
    grid.setAlive(5, 6);
    grid.setAlive(4, 5);
    grid.setAlive(5, 5);
    grid.setAlive(6, 5);
    
    grid.print();

    for (int i = 0; i < 8; i++) {
        grid.start();
        grid.print();    
    }
    // while (true) {
        
    // }
}

