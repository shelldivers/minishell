#ifndef MS_EXPAND_H
#define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

#include "libft.h"
#include "ft_bool.h"
#include "ms_env.h"

/* ms_expand.c */
char	**ms_expand(char **argv, t_env **env);

/* ms_expand_lst.c */
t_list	**ms_expand_init(char **argv);
char	**ms_expand_transform(t_list **head);
void	ms_expand_node_clear(t_list **head);

/* ms_expand_quote.c */
t_bool	ms_expand_quote(t_list **lst, t_list *node, int *idx, t_env **env);
t_bool	ms_expand_dquote(t_list **lst, t_list *node, int *idx, t_env **env);

/* ms_expand_escape.c */
t_bool	ms_expand_escape(t_list **lst, t_list *node, int *idx, t_env **env);

/* ms_expand_env.c */
t_bool	ms_expand_env(t_list **lst, t_list *node, int *idx, t_env **env);
t_bool	ms_expand_env_exchange(char **str, int *index, char *value);

/* ms_expand_wildcard.c */
t_bool	ms_expand_wildcard(t_list **lst, t_list *node, int *idx, t_env **env);

# ifdef __cplusplus
}
# endif

#endif
