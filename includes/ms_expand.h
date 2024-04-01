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

typedef struct s_queue
{
	struct s_list	*head;
	struct s_list	*tail;
	size_t	size;
}	t_queue;

typedef struct s_glob
{
	char	*content;
	char	*length;
	int		*index;
	size_t	index_size;
	char	*path;
	char	*rest;
	char	*pattern;
}	t_glob;

/* ms_expand.c */
char	**ms_expansion(char **argv, t_env *env, int status);

/* ms_expand_param.c */
t_bool	ms_expand_param(char **argv, t_env *env, int status);
/* ms_expand_param_utils.c */
char	*ms_status_expansion(char *str, char *pos, int status);
char	*ms_param_expansion(char *str, char *pos, t_env *env);

/* ms_expand_filename.c */
char	**ms_expand_filenames(char **argv);

/* ms_expand_utils.c */
void	ms_remove_quote(char *str);
void	ms_remove_dquote(char *_str);

# ifdef __cplusplus
}
# endif

#endif
