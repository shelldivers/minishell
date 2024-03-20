/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongwpa <jeongwpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:50:10 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/03/07 10:50:11 by jeongwpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXPAND_H
#define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

#include "ft_type.h"
#include "ms_env.h"
#include <dirent.h>

/* ms_expand.c */
char	**ms_expansion(char **argv, t_env *env, int status);

/* ms_expand_param.c */
t_bool	ms_expand_param(char **argv, t_env *env, int status);
char	*ms_status_expansion(char *str, char *pos, int status);
char	*ms_param_expansion(char *str, char *pos, t_env *env);

# ifdef __cplusplus
}
# endif

#endif
