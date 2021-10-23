cmake_minimum_required(VERSION 3.10)
project(tests C CXX)

set(PUSH_SWAP_SRCDIR ${PROJECT_SOURCE_DIR}/../srcs/${TERMCAP_VS})
set(LIBFT_DIR ${PROJECT_SOURCE_DIR}/../jwolflib)
set(LIBFT libft.a)
set(HEADERS catch.hpp)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

link_directories(${LIBFT_DIR})

include_directories(${PROJECT_SOURCE_DIR}/../includes ${LIBFT_DIR}/includes)

file(GLOB_RECURSE TEST_SOURCES
../srcs/push_swap/*.c
../srcs/checker/*.c
../srcs/utils/*.c
../srcs/utils/**/*.c
)

add_library(tester STATIC ${TEST_SOURCES})

file(GLOB_RECURSE SOURCES *.cpp)

add_executable(tests ${SOURCES})

add_dependencies(tests ${LIBFT})

target_link_libraries(tests tester ft)
