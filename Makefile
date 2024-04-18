NAME = minishell

S_INCLUDES = includes/
B_INCLUDES = includes_bonus/
LIBFT_INCLUDES = libft/includes

SOURCES = srcs/
S_PARSE = parser/
S_ERROR = error/
S_EXEC = exec/
S_BUILTIN = builtin/
S_ENV = env/
S_EXPAND = expand/
S_SIGNAL = signal/

B_SOURCES = srcs_bonus/
B_PARSE = parser/
B_ERROR = error/
B_EXEC = exec/
B_BUILTIN = builtin/
B_ENV = env/
B_EXPAND = expand/
B_SIGNAL = signal/

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

PARSER += ms_tokenizer.c ms_tokenizer2.c ms_clear.c ms_lexer.c ms_unterminal.c ms_unterminal2.c ms_terminal.c ms_parser.c ms_parser2.c\
			ms_parser_error_handler.c
ERROR += ms_error_utils.c  ms_error_utils2.c  ms_error_utils3.c ms_error.c 
EXEC += ms_exec.c ms_exec_utils.c ms_exec_utils2.c ms_exec_macro.c ms_exec_init_clear.c ms_exec_words.c ms_exec_path.c ms_exec_path2.c ms_exec_fd.c ms_quote_removal_dup.c \
			ms_exec_dup_pipe.c ms_exec_open_close_pipe.c ms_exec_commands.c ms_exec_io_redirect.c ms_exec_heredoc.c ms_exec_heredoc_before.c ms_exec_commands_fork.c \
			ms_exec_macro2.c
BUILTIN += ms_cd.c ms_echo.c ms_env.c ms_env_exec.c ms_exit.c ms_export.c ms_pwd.c ms_unset.c
ENV += ms_env_lst_utils.c ms_env_lst.c ms_env_serialize_utils.c ms_env_serialize.c
EXPAND += ms_expand.c ms_queue.c ms_queue_utils.c ms_glob.c ms_glob_utils.c \
			ms_expand_param.c ms_expand_param_utils.c ms_expand_param_utils2.c ms_expand_filename.c ms_expand_filenames.c ms_expand_filename_utils.c \
			ms_expand_filename_search.c ms_expand_filename_match1.c ms_expand_filename_match2.c ms_expand_filename_expand.c
SIGNAL += ms_signal_heredoc.c ms_signal_prompt.c ms_signal_utils.c

BS_PARSER += ms_tokenizer_bonus.c ms_tokenizer2_bonus.c ms_clear_bonus.c ms_lexer_bonus.c ms_unterminal_bonus.c ms_unterminal2_bonus.c ms_terminal_bonus.c ms_parser_bonus.c ms_parser2_bonus.c\
			ms_parser_error_handler_bonus.c
BS_ERROR += ms_error_utils_bonus.c  ms_error_utils2_bonus.c  ms_error_utils3_bonus.c ms_error_bonus.c 
BS_EXEC += ms_exec_bonus.c ms_exec_utils_bonus.c ms_exec_utils2_bonus.c ms_exec_macro_bonus.c ms_exec_init_clear_bonus.c ms_exec_words_bonus.c ms_exec_path_bonus.c ms_exec_path2_bonus.c ms_exec_fd_bonus.c ms_quote_removal_dup_bonus.c \
			ms_exec_dup_pipe_bonus.c ms_exec_open_close_pipe_bonus.c ms_exec_commands_bonus.c ms_exec_io_redirect_bonus.c ms_exec_heredoc_bonus.c ms_exec_heredoc_before_bonus.c ms_exec_commands_fork_bonus.c \
			ms_exec_macro2_bonus.c
BS_BUILTIN += ms_cd_bonus.c ms_echo_bonus.c ms_env_bonus.c ms_env_exec_bonus.c ms_exit_bonus.c ms_export_bonus.c ms_pwd_bonus.c ms_unset_bonus.c
BS_ENV += ms_env_lst_utils_bonus.c ms_env_lst_bonus.c ms_env_serialize_utils_bonus.c ms_env_serialize_bonus.c
BS_EXPAND += ms_expand_bonus.c ms_queue_bonus.c ms_queue_utils_bonus.c ms_glob_bonus.c ms_glob_utils_bonus.c \
			ms_expand_param_bonus.c ms_expand_param_utils_bonus.c ms_expand_param_utils2_bonus.c ms_expand_filename_bonus.c ms_expand_filenames_bonus.c ms_expand_filename_utils_bonus.c \
			ms_expand_filename_search_bonus.c ms_expand_filename_match1_bonus.c ms_expand_filename_match2_bonus.c ms_expand_filename_expand_bonus.c
BS_SIGNAL += ms_signal_heredoc_bonus.c ms_signal_prompt_bonus.c ms_signal_utils_bonus.c

M_FILES += minishell.c
M_FILES += $(addprefix $(S_PARSE), $(PARSER))
M_FILES += $(addprefix $(S_EXEC), $(EXEC))
M_FILES += $(addprefix $(S_BUILTIN), $(BUILTIN))
M_FILES += $(addprefix $(S_ENV), $(ENV))
M_FILES += $(addprefix $(S_ERROR), $(ERROR))
M_FILES += $(addprefix $(S_EXPAND), $(EXPAND))
M_FILES += $(addprefix $(S_SIGNAL), $(SIGNAL))

B_FILES += minishell_bonus.c
B_FILES += $(addprefix $(B_PARSE), $(BS_PARSER))
B_FILES += $(addprefix $(B_EXEC), $(BS_EXEC))
B_FILES += $(addprefix $(B_BUILTIN), $(BS_BUILTIN))
B_FILES += $(addprefix $(B_ENV), $(BS_ENV))
B_FILES += $(addprefix $(B_ERROR), $(BS_ERROR))
B_FILES += $(addprefix $(B_EXPAND), $(BS_EXPAND))
B_FILES += $(addprefix $(B_SIGNAL), $(BS_SIGNAL))

S_SRCS = $(addprefix $(SOURCES), $(M_FILES))
B_SRCS = $(addprefix $(B_SOURCES), $(B_FILES))
S_OBJS = $(S_SRCS:.c=.o)
B_OBJS = $(B_SRCS:.c=.o)

ifdef objs
	SRCS = $(B_SRCS)
	OBJS = $(B_OBJS)
	INCLUDES = $(B_INCLUDES)
else
	SRCS = $(S_SRCS)
	OBJS = $(S_OBJS)
	INCLUDES = $(S_INCLUDES)
endif

all: $(NAME) $(HEADER)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS) -I$(INCLUDES) -I$(LIBFT_INCLUDES) -lreadline  -Llibft -lft

bonus: 
	@make objs=1 all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDES) -I$(LIBFT_INCLUDES)

clean:
	make clean -C ./libft
	$(RM) $(S_OBJS) $(B_OBJS)

fclean: clean
	make fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
