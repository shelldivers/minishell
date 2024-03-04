#ifndef MS_ERROR_H
# define MS_ERROR_H

# include "ms_env.h"

void	ms_puterror_cmd_arg(t_env *env, char *cmd, char *arg);
void	ms_puterror_cmd(t_env *env, char *cmd);
void	ms_puterror_arg(t_env *env, char *arg);

#endif
