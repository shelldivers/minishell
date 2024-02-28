cmake_minimum_required(VERSION 3.25)

set(NAME minishell)
project(${NAME} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(libft)
add_subdirectory(~/./usr/local/lib/readline)

# add_subdirectory(googletest)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.x
)
FetchContent_MakeAvailable(googletest)

# 소스파일 및 헤더파일 목록
set(SRCS includes/minishell.h srcs/minishell.c srcs/init_clear.c srcs/separate_line.c srcs/tokenize.c)

add_library(${NAME} STATIC ${SRCS})
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
target_link_libraries(${NAME} libft)

add_subdirectory(test)