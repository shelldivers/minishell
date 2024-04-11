NAME = libft.a
SRCS_DIR = srcs
INCLUDES_DIR = includes
CC = cc
CFLAGS = -Wall -Wextra -Werror
FT_H = libft.h get_next_line.h ft_printf.h ft_bool.h ft_type.h
SRC = ft_isalpha.c ft_isdigit.c ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c
SRC += ft_lstiter.c ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memcpy.c ft_memset.c
SRC += ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_strncpy.c
SRC += ft_strndup.c ft_substr.c ft_strtrim.c ft_strrchr.c ft_strcmp.c ft_atoi.c ft_isalnum.c
SRC += ft_isnumeric.c ft_memmove.c
SRC += get_next_line.c get_next_line_utils.c
SRC += ft_printf.c ft_dprintf.c ft_sprintf.c
SRC += pf_handler.c pf_format.c pf_parse_char.c pf_parse_dec.c pf_parse_hex.c pf_parse_int.c
SRC += pf_parse_ptr.c pf_parse_str.c pf_parse_uint.c pf_parse_utils.c pf_strs_utils.c
SRCS = ${addprefix $(SRCS_DIR)/, $(SRC)}
OBJS = ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
