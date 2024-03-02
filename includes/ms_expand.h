#ifndef MS_EXPAND_H
#define MS_EXPAND_H

# ifdef __cplusplus
extern "C" {
# endif

#include "ft_bool.h"

char	**ms_expand(char **args);

t_bool	ms_expand_qv(char **args);
char	*ms_expand_qv_exchange(char *arg);
int		ms_expand_quote(char *arg, int *index);
void	ms_expand_dquote(char *arg, int *index);
void	ms_expand_escape(char *arg, int *index);


# ifdef __cplusplus
}
# endif

#endif
