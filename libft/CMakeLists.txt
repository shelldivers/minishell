cmake_minimum_required(VERSION 3.25)

set(NAME libft)

set(SRCS
        srcs/ft_isalpha.c
        srcs/ft_isdigit.c
        srcs/ft_lstadd_back.c
        srcs/ft_lstadd_front.c
        srcs/ft_lstclear.c
        srcs/ft_lstdelone.c
        srcs/ft_lstiter.c
        srcs/ft_lstlast.c
        srcs/ft_lstmap.c
        srcs/ft_lstnew.c
        srcs/ft_lstsize.c
        srcs/ft_memcpy.c
        srcs/ft_memset.c
        srcs/ft_printf.c
        srcs/ft_sprintf.c
        srcs/ft_dprintf.c
        srcs/pf_handler.c
        srcs/ft_strlen.c
        srcs/ft_strncpy.c
        srcs/ft_strndup.c
        srcs/ft_strncmp.c
        srcs/get_next_line.c
        srcs/get_next_line_utils.c
        srcs/pf_format.c
        srcs/pf_parse_char.c
        srcs/pf_parse_dec.c
        srcs/pf_parse_hex.c
        srcs/pf_parse_int.c
        srcs/pf_parse_ptr.c
        srcs/pf_parse_str.c
        srcs/pf_parse_uint.c
        srcs/pf_parse_utils.c
        srcs/pf_strs_utils.c
        srcs/ft_strjoin.c
        srcs/ft_strchr.c
        srcs/ft_substr.c
        srcs/ft_strdup.c
        srcs/ft_split.c
        srcs/ft_strtrim.c
        srcs/ft_strrchr.c
        includes/libft.h
        includes/ft_type.h
        includes/ft_printf.h
        includes/get_next_line.h
        includes/ft_bool.h
        srcs/ft_memmove.c
        srcs/ft_isalnum.c
        srcs/ft_strcmp.c
        srcs/ft_atoi.c
        srcs/ft_isnumeric.c
        )

add_library(${NAME} STATIC ${SRCS})

target_include_directories(${NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
