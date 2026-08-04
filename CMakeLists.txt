# zed
cmake_minimum_required(VERSION 3.10)
project(jongho-game-cpp)

# Zed(Clangd) 코드 자동완성을 위해 필수 추가
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 디버그 빌드 모드 활성화 (반드시 필요)
set(CMAKE_BUILD_TYPE Debug)

# 하위 프로젝트 폴더들을 등록
add_subdirectory(dominion)

# vscode
# cmake_minimum_required(VERSION 3.15)
# project(UIUC_CS_Fundamentals)

# # M1 Mac 및 C++20 표준 강제 설정
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # 테스트 빌드용 폴더 등록
# add_subdirectory(quick_sort)
