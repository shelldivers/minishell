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
	size_t	size;
	t_list	*head;
	t_list	*tail;
}	t_queue;

typedef struct s_glob
{
	char	*path;
	char	*prefix;
	char	*pattern;
	char	*suffix;
	char	*remain;
} t_glob;

/* ms_expand.c */
char	**ms_expansion(char **argv, t_env *env, int status);

/* ms_expand_param.c */
t_bool	ms_expand_param(char **argv, t_env *env, int status);
char	*ms_status_expansion(char *str, char *pos, int status);
char	*ms_param_expansion(char *str, char *pos, t_env *env);

/* ms_expand_filename.c */
char	**ms_expand_filename(char **argv, t_env *env);
char	**ms_expand_loop(t_queue *queue, char *str, t_env *env);

/* ms_expand_filename2.c */
t_bool	ms_filename_expansion(t_queue *queue, char *str, t_env *env);

/* ms_expand_filename3.c */
t_bool	ms_match_pattern(char *d_name, t_glob *glob);
t_bool	ms_match_type(struct dirent *entry, t_glob *glob);

/* ms_expand_glob.c */
t_glob	*ms_parse_glob(char *str);
t_glob	*ms_init_glob(void);
void	ms_destroy_glob(t_glob *glob);

/* ms_expand_glob2.c */
t_bool	ms_get_path(t_glob *glob, char *str);

/* ms_expand_glob3.c */
t_bool	ms_get_pattern(t_glob *glob, char *str);
t_bool	ms_get_remain(t_glob *glob, char *str);
t_bool	ms_parse_pattern(t_glob *glob);

/* ms_expand_queue.c */
t_queue	*ms_init_queue(void);
void	ms_destroy_queue(t_queue *queue);
void	ms_clear_queue(t_queue *queue);
t_bool	ms_enqueue(t_queue *queue, char *str);
t_list	*ms_dequeue(t_queue *queue);

/* ms_expand_queue2.c */
char	**ms_queue_to_array(t_queue *queue);

/* ms_expand_utils.c */
char	**ms_strsjoin(char ***dest, char **s2);

# ifdef __cplusplus
}
# endif

#endif
