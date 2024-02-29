#ifndef MINISHELL_H
# define MINISHELL_H
# include "ft_bool.h"
# include "ms_env.h"

# ifdef __cplusplus
extern "C" {
# endif

int	ms_cd(int argc, char **argv, t_env **env);
int	ms_pwd(int argc, char **argv);
int	ms_echo(int argc, char **argv);
int	ms_export(int argc, char **argv, t_env **env);
int	ms_unset(int argc, char **argv, t_env **env);
int	ms_env(int argc, char **argv, char **envp);
int	ms_exit(int argc, char **argv);

# ifdef __cplusplus
}
# endif

#endif