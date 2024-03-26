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
char	*ms_get_path(char *str);
char	*ms_get_pattern(char *str);

/* ms_expand_queue.c */
t_queue	*ms_init_queue(void);
void	ms_destroy_queue(t_queue *queue);
void	ms_clear_queue(t_queue *queue);
t_bool	ms_enqueue(t_queue *queue, char *str);
t_list	*ms_dequeue(t_queue *queue);

/* ms_expand_queue2.c */
char	**ms_queue_to_array(t_queue *queue);

# ifdef __cplusplus
}
# endif

#endif
