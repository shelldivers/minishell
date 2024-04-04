/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:50:08 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/04 20:49:15 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
void	ms_puterror_syntax(t_env **env, char *value);
void	ms_puterror_is_dir(char *path);
void	ms_puterror_no_file(char *path);
void	ms_puterror_fork(void);
void	ms_puterror_max_here_doc(void);
void	ms_puterror_no_command(char *path);

# ifdef __cplusplus
}
# endif

#endif
