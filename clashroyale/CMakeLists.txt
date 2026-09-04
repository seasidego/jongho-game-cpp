# zed
project(clashroyale) # _exe를 빼고 깔끔하게 작성

find_package(raylib REQUIRED)

# 1. Google Test 패키지 찾기
find_package(GTest REQUIRED)

# 현재 디렉토리와 clashroyale 폴더 안의 모든 .cpp 파일을 자동으로 찾아서 SRC_FILES 변수에 저장
file(GLOB_RECURSE SRC_FILES "*.cpp")

file(GLOB_RECURSE SRC_FILES 
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} 
    CONFIGURE_DEPENDS
    "*.cpp"
)
# 찾은 파일 목록 중 build나 .cache 경로가 포함된 임시 파일들을 필터링하여 제거합니다.
list(FILTER SRC_FILES EXCLUDE REGEX "build/|\\.cache/")

# 자동으로 찾아낸 모든 파일로 실행 파일 생성
add_executable(clashroyale ${SRC_FILES})

# 2. 헤더 파일 경로 포함하기
include_directories(${GTEST_INCLUDE_DIRS})

# 3. clashroyale 타겟에 gtest 라이브러리 링크하기
# (기존 add_executable(clashroyale ...) 정의 아래에 추가하세요)
target_link_libraries(clashroyale PRIVATE GTest::gtest GTest::gtest_main)
target_link_libraries(clashroyale PRIVATE raylib)

# include(FetchContent)
# FetchContent_Declare(
#     raylib
#     URL https://github.com
# )

# # 불필요한 예제 파일 빌드를 제외하여 다운로드 및 빌드 속도 최적화
# set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) 
# FetchContent_MakeAvailable(raylib)

# # 4. 생성된 실행 파일에 Raylib 라이브러리 연결
# target_link_libraries(clashroyale PRIVATE raylib)