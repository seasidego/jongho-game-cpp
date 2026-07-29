#include <iostream>
#include <format>
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
    return 0;
}
