#ifndef MS_ERROR_H
# define MS_ERROR_H

# ifdef __cplusplus
extern "C" {
# endif

# include "ms_env.h"

void	ms_puterror_cmd_arg(t_env *env, char *cmd, char *arg);
void	ms_puterror_cmd(t_env *env, char *cmd);
void	ms_puterror_arg(t_env *env, char *arg);

void	ms_puterror_identifier(t_env *env, char *cmd, char *arg);
void	ms_puterror_numeric(t_env *env, char *cmd, char *arg);
void	ms_puterror_too_many_args(t_env *env, char *cmd);
void	ms_puterror_env_not_set(t_env *env, char *cmd, char *key);

# ifdef __cplusplus
}
# endif

#endif
