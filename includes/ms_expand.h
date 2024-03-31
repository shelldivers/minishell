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
	char	*content;
	t_queue	*pattern;
	char	*prefix;
	char	*suffix;
	char	*remain;
}	t_glob;

/* ms_expand.c */
char	**ms_expansion(char **argv, t_env *env, int status);

/* ms_expand_param.c */
t_bool	ms_expand_param(char **argv, t_env *env, int status);
char	*ms_status_expansion(char *str, char *pos, int status);
char	*ms_param_expansion(char *str, char *pos, t_env *env);

/* ms_expand_filename.c */
char	**ms_expand_filenames(char **argv);
/* ms_expand_filenames1.c */
char	**ms_expand_filename(t_queue *queue, char *str);
/* ms_expand_filenames1_utils.c */
void	inspect_filename(t_queue *queue);
/* ms_expand_filename2.c */
t_bool	ms_expand_filename_search(t_queue *queue, int size);
/* ms_expand_filename3.c */
t_bool	ms_expand_filename_expansion(t_queue *queue, t_glob *glob, char *str);
/* ms_expand_filename3_utils.c */
char	*join_path(char *entry, t_glob *glob);
t_bool	ms_match_pattern(char *d_name, t_glob *glob);
t_bool	ms_match_type(struct dirent *entry, t_glob *glob);

/* ms_expand_glob.c */
t_glob	*ms_init_glob(char *str);
void	ms_destroy_glob(t_glob *glob);
/* ms_expand_glob_utils.c */
t_bool	ms_parse_glob(t_glob *glob, char *pos);
/* ms_expand_glob_utils2.c */
t_bool	ms_parse_patterns(t_glob *glob, char *str, char *pos);
t_bool	ms_parse_pattern(t_glob *glob);
/* ms_expand_glob_utils3.c */
t_bool	ms_enqueue_patterns(t_glob *glob, char *pos1);

/* ms_expand_queue.c */
t_queue	*ms_init_queue(void);
void	ms_destroy_queue(t_queue *queue);
void	ms_clear_queue(t_queue *queue);
t_bool	ms_enqueue(t_queue *queue, char *str);
t_list	*ms_dequeue(t_queue *queue);
/* ms_expand_queue2.c */
void	ms_pick_queue(t_queue *queue, t_list *node);
t_queue	*ms_enqueue_arrays(t_queue *queue, char **arrays);
char	**ms_queue_to_arrays(t_queue *queue);
/* ms_expand_utils.c */
void	ms_remove_dquote(char *_str);
void	ms_remove_quote(char *str);

# ifdef __cplusplus
}
# endif

#endif
