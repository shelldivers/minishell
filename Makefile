NAME = minishell

INCLUDES = includes/
LIBFT_INCLUDES = libft/includes

SOURCES = srcs/
S_PARSE = parser/
S_ERROR = error/
S_EXEC = exec/
S_BUILTIN = builtin/
S_ENV = env/

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

PARSER += ms_tokenizer.c ms_tokenizer2.c ms_init.c ms_clear.c ms_lexer.c ms_unterminal.c ms_unterminal2.c ms_terminal.c ms_terminal2.c ms_parser.c 
ERROR += ms_error_utils.c ms_error.c
EXEC += ms_exec.c ms_exec_unit.c ms_words.c
BUILTIN += ms_cd.c ms_echo.c ms_env.c ms_exit.c ms_export.c ms_pwd.c ms_unset.c
ENV += ms_env_lst_utils.c ms_env_lst.c ms_env_serialize_utils.c ms_env_serialize.c


M_FILES += minishell.c
M_FILES += $(addprefix $(S_PARSE), $(PARSER))
M_FILES += $(addprefix $(S_EXEC), $(EXEC))

B_FILES += minishell.c
B_FILES += $(addprefix $(S_PARSE), $(PARSER))

ifdef objs
SRCS = $(addprefix $(SOURCES), $(B_FILES))
OBJS = $(SRCS:.c=.o)
HEADER = $(addprefix $(INCLUDES), $(H_FILES))
else
SRCS = $(addprefix $(SOURCES), $(M_FILES))
OBJS = $(SRCS:.c=.o)
HEADER = $(addprefix $(INCLUDES), $(H_FILES))
endif

all: $(NAME) $(HEADER)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) -I$(INCLUDES) -I$(LIBFT_INCLUDES) -lreadline  -Llibft -lft

bonus: 
	make objs=1 all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES) -I$(LIBFT_INCLUDES)

clean:
	make clean -C ./libft
	$(RM) $(SRCS:.c=.o) $(SRCS:.c=.o)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY:all bonus clean fclean re
