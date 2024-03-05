#ifndef MS_EXPAND_H
#define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

#include "ft_bool.h"
#include "ms_env.h"

/* ms_expand.c */
char	**ms_expand(char **args, t_env **env);

/* ms_expand_qv.c */
t_bool	ms_expand_qv(char **args, t_env **env);
char	*ms_expand_qv_exchange(char **str, t_env **env);

/* ms_expand_qv_utils.c */
t_bool	ms_expand_env_exchange(char **str, int *index, char *value);
t_bool	ms_expand_env(char **str, int *index, t_env **env);
void	ms_expand_escape(char *arg, int *index);
int		ms_expand_quote(char *arg, int *index);
void	ms_expand_dquote(char *arg, int *index, t_env **env);

/* ms_expand_aster.c */
char	**ms_expand_aster(char **args, t_env **env);

# ifdef __cplusplus
}
# endif

#endif
