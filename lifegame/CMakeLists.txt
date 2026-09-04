# zed
project(lifegame) # _exe를 빼고 깔끔하게 작성

# 프로젝트 이름(quick_sort) 그대로 실행 파일이 생성됩니다.
# 현재 디렉토리와 dominion 폴더 안의 모든 .cpp 파일을 자동으로 찾아서 SRC_FILES 변수에 저장
# file(GLOB_RECURSE SRC_FILES "*.cpp")

file(GLOB_RECURSE SRC_FILES 
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    CONFIGURE_DEPENDS
    "*.cpp"
)
# 찾은 파일 목록 중 build나 .cache 경로가 포함된 임시 파일들을 필터링하여 제거합니다.
list(FILTER SRC_FILES EXCLUDE REGEX "build/|\\.cache/")

# 자동으로 찾아낸 모든 파일로 실행 파일 생성
add_executable(lifegame ${SRC_FILES})

# 1. Google Test 패키지 찾기
find_package(GTest REQUIRED)

# 2. 헤더 파일 경로 포함하기
include_directories(${GTEST_INCLUDE_DIRS})

# 3. lifegame 타겟에 gtest 라이브러리 링크하기
# (기존 add_executable(lifegame ...) 정의 아래에 추가하세요)
target_link_libraries(lifegame PRIVATE GTest::gtest GTest::gtest_main)

