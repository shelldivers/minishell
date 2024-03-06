#ifndef MS_EXPAND_H
#define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

#include "libft.h"
#include "ft_bool.h"
#include "ms_env.h"
#include <dirent.h>

/* ms_expand.c */
char	**ms_expand(char **argv, t_env **env);

/* ms_expand_lst.c */
t_list	**ms_expand_init(char **argv);
char	**ms_expand_transform_free(t_list **head);

/* ms_expand_quote.c */
t_bool	ms_expand_quote(t_list **lst, t_list **node, int *idx, t_env **env);
t_bool	ms_expand_dquote(t_list **lst, t_list **node, int *idx, t_env **env);

/* ms_expand_escape.c */
t_bool	ms_expand_escape(t_list **lst, t_list **node, int *idx, t_env **env);

/* ms_expand_env.c */
t_bool	ms_expand_env(t_list **lst, t_list **node, int *idx, t_env **env);

/* ms_expand_wildcard.c */
t_bool	ms_expand_wildcard(t_list **lst, t_list **node, int *idx, t_env **env);
void	ms_wildcard_replace(t_list **head, t_list **node, t_list **ext);
t_list	**ms_wildcard_extend(DIR *dir, char *str);
t_list	**ms_wildcard_dir_loop(DIR *dir, char *prefix, char *suffix);
t_bool	ms_wildcard_add(t_list **head, char *d_name, char *prefix, char *suffix);

/* ms_expand_wildcard_utils.c */
char	*ms_wildcard_get_path(char *str);
char	*ms_wildcard_get_prefix(char *str);
char	*ms_wildcard_get_suffix(char *str);
char	*ms_wildcard_get_match(char *str);
char	*ms_wildcard_combine(char *d_name, char *prefix, char *suffix);
t_bool	ms_wildcard_is_match(char *name, int type, char *match, char *suffix);

# ifdef __cplusplus
}
# endif

#endif
