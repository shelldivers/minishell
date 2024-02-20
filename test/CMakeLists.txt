cmake_minimum_required(VERSION 3.25)

set(NAME minishell_test)

# 소스 파일 목록
set(SRCS minishell_test.cpp echo_test.cpp)

add_executable(${NAME} ${SRCS})

target_link_libraries(${NAME} PUBLIC minishell gtest_main)

add_test(
        NAME ${NAME}
        COMMAND ${NAME}
)