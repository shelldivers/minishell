NAME = minishell

INCLUDES = ./includes/
SOURCES = ./srcs/parser/

CC = cc

# CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

RM = rm -rf

B_FILES = \
minishell.c \
lexer.c \
lexer2.c \
init.c \
clear.c \
tokenizer.c \
unterminal.c \
unterminal2.c \
terminal.c \
terminal2.c \
parser.c 

M_FILES = \
minishell.c \
lexer.c \
lexer2.c \
init.c \
clear.c \
tokenizer.c \
unterminal.c \
unterminal2.c \
terminal.c \
terminal2.c \
parser.c 

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
