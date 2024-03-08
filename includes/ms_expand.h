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

# define WILDCARD (void *)1

# ifdef __cplusplus
extern "C" {
# endif

# define NO_MATCH 1
# define MATCH 0
# define ERROR (-1)

#include "ft_type.h"
#include "ms_env.h"
#include <dirent.h>

typedef struct s_wildcard
{
	char	*prefix;
	char	*suffix;
	char	*last;
}	t_wildcard;

typedef struct s_exp
{
	int	depth;
	int	*exit_code;
}	t_exp;

/* ms_expand.c */
char	**ms_expand(char **argv, t_env **env, int *exit);
t_bool	ms_expand_proceed(t_list **head, t_env **env, t_exp exp);
t_bool	ms_expand_handler(t_list **head, t_list **node, t_env **env, t_exp exp);
t_bool	ms_expand_route(t_list **node, int *idx, t_env **env, t_exp exp);

/* ms_expand_lst.c */
t_list	**ms_expand_init(char **argv);
char	**ms_expand_transform_free(t_list **head);

/* ms_expand_quote.c */
t_bool	ms_expand_quote(t_list **node, int *idx);
t_bool	ms_expand_dquote(t_list **node, int *idx, t_env **env, t_exp exp);

/* ms_expand_escape.c */
t_bool	ms_expand_escape(t_list **node, int *idx);

/* ms_expand_env.c */
t_bool	ms_expand_env(t_list **node, int *idx, t_env **env, int *exit_code);
t_bool	ms_expand_reserved(t_list **node, int *idx, const int *exit_code);

/* ms_expand_wildcard.c */
int		ms_expand_wildcard(t_list **head, t_list **nod, t_env **env, t_exp exp);
t_list	**ms_wildcard_loop(t_list **node, t_env **env, t_exp exp);
t_list	*ms_wildcard_replace(t_list **head, t_list **node, t_list **extend);
t_list	*ms_wildcard_remove(t_list **head, t_list **remove);

/* ms_wildcard_dir.c */
t_list	**ms_wildcard_extend(DIR *dir, char *path, char *str);
t_list	**ms_wildcard_d_loop(DIR *dir, char *path, t_wildcard *wc);
t_bool	ms_wildcard_add(t_list **head, char *name, char *prefix, char *last);
t_bool	ms_wildcard_is_type(char hidden, int type, t_wildcard *wc);
t_bool	ms_wildcard_is_match(char *name, t_wildcard *wc);

/* ms_expand_wildcard_utils.c */
char	*ms_wildcard_get_path(char *str);
char	*ms_wildcard_get_last(char *str);
char	*ms_wildcard_get_prefix(char *str);
char	*ms_wildcard_get_suffix(char *str);
char	*ms_wildcard_combine(char *d_name, char *path, char *last);

# ifdef __cplusplus
}
# endif

#endif
