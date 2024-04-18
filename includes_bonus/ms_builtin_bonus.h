/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_builtin_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:50:04 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/15 20:27:41 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_BUILTIN_BONUS_H
# define MS_BUILTIN_BONUS_H
# include "ms_env_bonus.h"

int	ms_cd(int argc, char **argv, t_env **env);
int	ms_pwd(int argc, char **argv, t_env **env);
int	ms_echo(int argc, char **argv, t_env **env);
int	ms_export(int argc, char **argv, t_env **env);
int	ms_unset(int argc, char **argv, t_env **env);
int	ms_env(int argc, char **argv, t_env **envp);
int	ms_exit(int argc, char **argv, t_env **env, int pipe_idx);
int	ms_env_exec(char *line, char **envp);

#endif
