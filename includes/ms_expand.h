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
char	**ms_expansion(char **argv, t_env *env);

/* ms_expand_tilde.c */
void	ms_tilde_expansion(char **argv, t_env *env);


# ifdef __cplusplus
}
# endif

#endif
