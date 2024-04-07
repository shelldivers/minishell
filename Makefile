NAME = minishell

INCLUDES = includes/
LIBFT_INCLUDES = libft/includes

SOURCES = srcs/
S_PARSE = parser/
S_ERROR = error/
S_EXEC = exec/
S_BUILTIN = builtin/
S_ENV = env/
S_EXPAND = expand/
S_SIGNAL = signal/

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

PARSER += ms_tokenizer.c ms_tokenizer2.c ms_clear.c ms_lexer.c ms_unterminal.c ms_unterminal2.c ms_terminal.c ms_parser.c ms_parser2.c\
			ms_parser_error_handler.c
ERROR += ms_error_utils.c  ms_error_utils2.c  ms_error_utils3.c ms_error.c 
EXEC += ms_exec.c ms_exec_utils.c ms_exec_utils2.c ms_exec_macro.c ms_exec_init_clear.c ms_exec_words.c ms_exec_path.c ms_exec_fd.c ms_quote_removal_dup.c \
			ms_exec_dup_pipe.c ms_exec_open_close_pipe.c ms_exec_commands.c ms_exec_io_redirect.c ms_exec_heredoc.c ms_exec_heredoc_before.c ms_exec_commands_fork.c \
			ms_exec_macro2.c
BUILTIN += ms_cd.c ms_echo.c ms_env.c ms_env_exec.c ms_exit.c ms_export.c ms_pwd.c ms_unset.c
ENV += ms_env_lst_utils.c ms_env_lst.c ms_env_serialize_utils.c ms_env_serialize.c
EXPAND += ms_expand.c ms_queue.c ms_queue_utils.c ms_glob.c ms_glob_utils.c \
			ms_expand_param.c ms_expand_param_utils.c ms_expand_filename.c ms_expand_filenames.c ms_expand_filename_utils.c \
			ms_expand_filename_search.c ms_expand_filename_match1.c ms_expand_filename_match2.c ms_expand_filename_expand.c
SIGNAL += ms_signal_heredoc.c ms_signal_prompt.c ms_signal_utils.c

M_FILES += minishell.c
M_FILES += $(addprefix $(S_PARSE), $(PARSER))
M_FILES += $(addprefix $(S_EXEC), $(EXEC))
M_FILES += $(addprefix $(S_BUILTIN), $(BUILTIN))
M_FILES += $(addprefix $(S_ENV), $(ENV))
M_FILES += $(addprefix $(S_ERROR), $(ERROR))
M_FILES += $(addprefix $(S_EXPAND), $(EXPAND))
M_FILES += $(addprefix $(S_SIGNAL), $(SIGNAL))

B_FILES += minishell.c
B_FILES += $(addprefix $(S_PARSE), $(PARSER))
B_FILES += $(addprefix $(S_EXEC), $(EXEC))
B_FILES += $(addprefix $(S_BUILTIN), $(BUILTIN))
B_FILES += $(addprefix $(S_ENV), $(ENV))
B_FILES += $(addprefix $(S_ERROR), $(ERROR))
B_FILES += $(addprefix $(S_EXPAND), $(EXPAND))
B_FILES += $(addprefix $(S_SIGNAL), $(SIGNAL))

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
	$(CC) -g $(CFLAGS) -o $(NAME) $(SRCS) -I$(INCLUDES) -I$(LIBFT_INCLUDES) -lreadline  -Llibft -lft

bonus: 
	make objs=1 all

%.o: %.c
	$(CC) -g $(CFLAGS) -c $< -o $@ -I$(INCLUDES) -I$(LIBFT_INCLUDES)

clean:
	make clean -C ./libft
	$(RM) $(SRCS:.c=.o)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
