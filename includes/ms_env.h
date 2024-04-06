/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:50:06 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:50:06 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENV_H
# define MS_ENV_H
# include "ft_bool.h"
# include <stdlib.h>

# define HOME "HOME"
# define PWD "PWD"
# define OLDPWD "OLDPWD"
# define SHELL "SHELL"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* ms_env.c */
void	ms_env_remove(t_env **head, char *key);
char	*ms_getenv(t_env *env, char *key);
t_bool	ms_setenv(t_env **head, char *key, char *value);

/* ms_env_utils.c */
t_bool	ms_is_valid_env_key(char *key);
void	ms_env_clear(t_env **head);
size_t	ms_env_size(t_env *head);
t_env	*ms_env_push_back(t_env **head, t_env *env);
void	ms_env_print_all(t_env *env);

/* ms_env_serialize.c */
char	**ms_env_serialize(t_env *env);
char	**ms_env_serialize_union(t_env **env1, t_env **env2);
t_env	**ms_env_deserialize(char **envp);

/* ms_env_serialize_utils.c */
t_bool	ms_env_move(char **envp, t_env **env, size_t start);
t_env	*ms_str_to_env(char *str);
char	*ms_env_to_str(t_env *env);

#endif
