cmake_minimum_required(VERSION 3.25)

set(NAME minishell)
project(${NAME} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(libft)

# add_subdirectory(googletest)
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.x
)
FetchContent_MakeAvailable(googletest)

# 소스파일 및 헤더파일 목록
set(SRCS includes/minishell.h
        srcs/expand/ms_expand.c
        includes/ms_expand.h
        includes/ms_env.h
        srcs/minishell.c
        srcs/builtin/ms_cd.c
        srcs/builtin/ms_pwd.c
        srcs/builtin/ms_echo.c
        srcs/env/ms_env_lst.c
        srcs/env/ms_env_serialize_utils.c
        srcs/env/ms_env_lst_utils.c
        srcs/builtin/ms_export.c
        srcs/env/ms_env_serialize.c
        srcs/builtin/ms_unset.c
        srcs/builtin/ms_env.c
        srcs/builtin/ms_exit.c
        srcs/error/ms_error.c
        includes/ms_error.h
        includes/ms_builtin.h
        srcs/error/ms_error_utils.c
        srcs/expand/ms_expand_param.c
        srcs/expand/ms_expand_filenames.c
        srcs/parser/ms_init.c
        srcs/parser/ms_lexer.c
        srcs/parser/ms_parser.c
        srcs/parser/ms_terminal2.c
        srcs/parser/ms_tokenizer.c
        srcs/parser/ms_tokenizer2.c
        srcs/parser/ms_unterminal.c
        srcs/parser/ms_unterminal2.c
        srcs/parser/ms_clear.c
        srcs/parser/ms_terminal.c
        srcs/expand/ms_queue.c srcs/expand/ms_queue_utils.c srcs/expand/ms_expand_filename_search.c srcs/expand/ms_glob_utils.c srcs/expand/ms_glob.c srcs/expand/ms_expand_utils.c srcs/expand/ms_expand_filename_expansion.c srcs/expand/ms_expand_filename.c srcs/expand/ms_expand_filename_expandsion_utils.c srcs/expand/ms_expand_filename_utils.c srcs/expand/ms_expand_param_utils.c srcs/expand/ms_glob_utils2.c)

add_library(${NAME} STATIC ${SRCS})
target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/includes)
target_link_libraries(${NAME} libft)

add_subdirectory(test)