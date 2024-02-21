#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>

# ifdef __cplusplus
extern "C" {
# endif

extern int	errno;

int	ms_cd(int argc, char **argv);
int	ms_pwd(int argc, char **argv);
int	ms_echo(int argc, char **argv);

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ms_env.c */
t_env	**ms_env_deserialize(char **envp);
char	**ms_env_serialize(t_env *env);
size_t	ms_env_size(t_env *head);
void	ms_env_clear(t_env **head);
t_env	*ms_env_push_back(t_env **head, t_env *env);

/* ms_env_utils.c */
t_env	*ms_str_to_env(char *str);
char	*ms_env_to_str(t_env *env);

# ifdef __cplusplus
}
# endif

#endif