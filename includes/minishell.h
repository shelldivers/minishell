#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef __cplusplus
extern "C" {
# endif

int	ms_cd(int argc, char **argv);
int	ms_pwd(int argc, char **argv);
int	ms_echo(int argc, char **argv);

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	**g_env;

/* ms_env_utils.c */
t_env	*ms_str_to_env(char *str);
char	*ms_env_to_str(t_env *env);

# ifdef __cplusplus
}
# endif

#endif