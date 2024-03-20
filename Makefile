NAME = minishell

INCLUDES = includes/
SOURCES = srcs/
S_PARSE = parser/

CC = cc
# CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf

PARSER += ms_minishell.c ms_lexer.c ms_lexer2.c ms_init.c ms_clear.c ms_tokenizer.c ms_unterminal.c ms_unterminal2.c ms_terminal.c ms_terminal2.c ms_parser.c 

B_FILES += $(addprefix $(S_PARSE), $(PARSER))

M_FILES += $(addprefix $(S_PARSE), $(PARSER))


H_FILES = \
minishell.h \

LIBFT = libft/libft.a

ifdef objs
SRCS = $(addprefix $(SOURCES), $(B_FILES))
OBJS = $(SRCS:.c=.o)
HEADER = $(addprefix $(INCLUDES), $(H_FILES))
else
SRCS = $(addprefix $(SOURCES), $(M_FILES))
OBJS = $(SRCS:.c=.o)
HEADER = $(addprefix $(INCLUDES), $(H_FILES))
endif

CASE =


all: $(NAME) $(HEADER)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRCS) -I $(INCLUDES) $(LIBFT) -lreadline
# 제출용 : $(CC) $(CFLAGS) -o $(NAME) $(OBJS)
# lldb용 : $(CC) -g $(CFLAGS) -o $(NAME) $(MSRCS)
# sanitize용 : $(CC) -fsanitize=address $(CFLAGS) -o $(NAME) $(MSRCS)

test: $(NAME)
	./$(NAME) $(CASE)

leak: $(NAME)
	valgrind --leak-check=full ./$(NAME) $(CASE)
# --leak-check=full --show-leak-kinds=all --track-origins=yes

# bonus: 
# 	make objs=1 all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES)

clean:
	make clean -C ./libft
	$(RM) $(SRCS:.c=.o) $(SRCS:.c=.o)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY:all bonus clean fclean re
