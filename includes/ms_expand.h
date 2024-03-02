#ifndef MS_EXPAND_H
#define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

#include "ft_bool.h"

/* ms_expand.c */
char	**ms_expand(char **args);

/* ms_expand_qv.c */
t_bool	ms_expand_qv(char **args);
char	*ms_expand_qv_exchange(char *arg);

/* ms_expand_qv_utils.c */
t_bool	ms_expand_env_exchange(char **arg, int *index, char *value);
t_bool	ms_expand_env(char **arg, int *index);
void	ms_expand_escape(char *arg, int *index);
int		ms_expand_quote(char *arg, int *index);
void	ms_expand_dquote(char *arg, int *index);

/* ms_expand_aster.c */
char	**ms_expand_aster(char **args);

# ifdef __cplusplus
}
# endif

#endif
