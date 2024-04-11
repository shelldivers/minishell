/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:50:08 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/05 16:35:02 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ERROR_H
# define MS_ERROR_H
# define MINISHELL "minishell"
# define ERROR (-1)
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
void	ms_puterror_ambiguous_redirect(char *path);
void	ms_puterror_syntax_newline(void);

#endif
