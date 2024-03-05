#ifndef MS_EXPAND_H
#define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

#include "ft_bool.h"
#include "ms_env.h"

/* ms_expand.c */
t_bool	ms_expand(char **argv, t_env **env);

/* ms_expand_quote.c */
void	ms_expand_quote(char *str, int *index);
void	ms_expand_dquote(char *str, int *index, t_env **env);

/* ms_expand_escape.c */
void	ms_expand_escape(char *str, int *index);

/* ms_expand_env.c */
t_bool	ms_expand_env(char **str, int *index, t_env **env);
t_bool	ms_expand_env_exchange(char **str, int *index, char *value);

/* ms_expand_wildcard.c */
char	**ms_expand_wildcard(char **args, int *index, t_env **env);

# ifdef __cplusplus
}
# endif

#endif
