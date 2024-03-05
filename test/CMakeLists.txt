cmake_minimum_required(VERSION 3.25)

set(NAME minishell_test)

# 소스 파일 목록
set(SRCS minishell_test.cpp cd_test.cpp pwd_test.cpp echo_test.cpp env_test.cpp ft_strcmp_test.cpp export_test.cpp unset_test.cpp error_test.cpp exit_test.cpp)

add_executable(${NAME} ${SRCS})

target_link_libraries(${NAME} PUBLIC minishell libft gtest_main)

add_test(
        NAME ${NAME}
        COMMAND ${NAME}
)