cmake_minimum_required(VERSION 3.25)

set(NAME minishell_test)

# 소스 파일 목록
set(SRCS minishell_test.cpp
        expand_qv_test.cpp
        ft_memmove_test.cpp
        expand_quote_test.cpp
        expand_dquote_test.cpp
        ms_expand_escape_test.cpp)

add_executable(${NAME} ${SRCS})

target_link_libraries(${NAME} PUBLIC minishell gtest_main)

add_test(
        NAME ${NAME}
        COMMAND ${NAME}
)