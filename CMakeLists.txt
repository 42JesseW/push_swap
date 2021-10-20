cmake_minimum_required(VERSION 3.10)
project(push_swap C)

set(CMAKE_C_STANDARD 99)
set(HEADERS includes/push_swap.h)
set(LIBFT_DIR ${PROJECT_SOURCE_DIR}/libft)
set(LIBFT libft.a)

include_directories(includes)
link_directories(${LIBFT_DIR})

add_custom_target(
    ${LIBFT} ALL
    COMMAND make
    WORKING_DIRECTORY ${LIBFT_DIR}
)
file(GLOB_RECURSE SRC_UTILS srcs/utils/*.c)
file(GLOB_RECURSE SRC_CHECKER srcs/checker/*.c)
file(GLOB_RECURSE SRC_PUSH_SWAP srcs/push_swap/*.c)

add_executable(checker ${SRC_UTILS} ${SRC_CHECKER})
add_executable(push_swap ${SRC_UTILS} ${SRC_PUSH_SWAP})

add_dependencies(checker ${LIBFT})
add_dependencies(push_swap ${LIBFT})

target_link_libraries(checker ft)
target_link_libraries(push_swap ft)

add_subdirectory(tests)