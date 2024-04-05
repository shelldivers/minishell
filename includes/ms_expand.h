/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_expand.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:50:10 by jeongwpa          #+#    #+#             */
/*   Updated: 2024/04/05 13:56:07 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_EXPAND_H
# define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

# define ASTERISK (-1)
# define CSPN " \t\n\"'\\$"

# include "ft_type.h"
# include "ms_env.h"
# include <dirent.h>

typedef struct s_queue
{
	struct s_list	*head;
	struct s_list	*tail;
	size_t			size;
}	t_queue;

typedef struct s_glob
{
	char	*content;
	char	*path;
	char	*pattern;
	char	*rest;
}	t_glob;

typedef struct s_table
{
	int	**arr;
	int	x;
	int	y;
}	t_table;

/* ms_expand.c */
char	**ms_expansion(char **argv, t_env *env, int status);

/* ms_expand_param.c */
t_bool	ms_expand_param(char **argv, t_env *env, int status);
/* ms_expand_param_utils.c */
char	*ms_status_expansion(char *str, char *pos, int status);
char	*ms_param_expansion(char *str, char *pos, t_env *env);

/* ms_expand_filenames.c */
char	**ms_expand_filenames(char **argv);
/* ms_expand_filename.c */
char	**ms_expand_filename(char *str);
/* ms_expand_filename_utils.c */
char	**ms_inspect_filename(t_queue *queue, int depth, char *str);
/* ms_expand_filename_search.c */
t_bool	ms_expand_filename_search(t_queue *queue, size_t size);
/* ms_expand_filename_expand.c */
t_bool	ms_expand_filename_expand(t_queue *queue, t_glob *glob);
/* ms_expand_filename_match1.c */
t_bool	ms_match(struct dirent *entry, t_glob *glob);
t_bool	match_type(struct dirent *entry, t_glob *glob);
char	*ms_join_path(t_glob *glob, char *d_name);
/* ms_expand_filename_match2.c */
t_bool	match_pattern(char *d_name, char *pattern);

/* ms_glob.c */
t_glob	*ms_init_glob(char *str);
void	ms_destroy_glob(t_glob *glob);
/* ms_glob_utils.c */
t_bool	ms_parse_glob(t_glob *glob);

/* ms_queue.c */
t_queue	*ms_init_queue(void);
t_bool	ms_enqueue(t_queue *queue, void *content);
t_list	*ms_dequeue(t_queue *queue);
void	ms_destroy_queue(t_queue *queue, void *del);
/* ms_queue_utils.c */
void	ms_queue_remove(t_queue *queue, t_list *target, void *del);
t_bool	ms_enqueue_array(t_queue *queue, char **array);
char	**ms_queue_to_array(t_queue *queue);

# ifdef __cplusplus
}
# endif

#endif
