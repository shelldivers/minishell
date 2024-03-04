NAME = minishell

INCLUDES = ./includes/
SOURCES = ./srcs/

CC = cc

# CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

RM = rm -rf

B_FILES = \
minishell.c \
separate_line.c \
init.c \
clear.c \
tokenize.c

M_FILES = \
minishell.c \
separate_line.c \
init.c \
clear.c \
tokenize.c

H_FILES = \
minishell.h

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
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRCS) -I $(INCLUDES) -lreadline
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
	$(RM) $(SRCS:.c=.o) $(SRCS:.c=.o)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY:all bonus clean fclean re
