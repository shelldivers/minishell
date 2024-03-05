#ifndef MS_BUILTIN_H
# define MS_BUILTIN_H

# ifdef __cplusplus
extern "C" {
# endif

# include "ms_env.h"

int	ms_cd(int argc, char **argv, t_env **env);
int	ms_pwd(int argc, char **argv, t_env **env);
int	ms_echo(int argc, char **argv, t_env **env);
int	ms_export(int argc, char **argv, t_env **env);
int	ms_unset(int argc, char **argv, t_env **env);
int	ms_env(int argc, char **argv, t_env **envp);
int	ms_exit(int argc, char **argv, t_env **env);

# ifdef __cplusplus
}
# endif

#endif
