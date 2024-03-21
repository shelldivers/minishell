#include "ms_expand.h"
#include "ms_env.h"
#include <dirent.h>

char	**ms_filename_expansion(char *str, t_env *env)
{

}

/**
* @details filename expansion\n
* - `*`를 제외한 다른 특수 패턴을 처리하지 않습니다.
* @see https://runebook.dev/ko/docs/bash/pattern-matching
*/
char	**ms_expand_filename(char **argv, t_env *env)
{
	char	**expanded;

	while (*argv)
	{
		expanded = ms_filename_expansion(*argv, env);
		if (expanded)
		{
			free(*argv);
			*argv = *expanded;
			free(expanded);
		}
		argv++;
	}
}
