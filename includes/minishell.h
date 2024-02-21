#ifndef MINISHELL_H
# define MINISHELL_H

# ifdef __cplusplus
extern "C" {
# endif

extern int	errno;

int	cd(int argc, char **argv);
int	ms_pwd(int argc, char **argv);
int	echo(int argc, char **argv);

# ifdef __cplusplus
}
# endif

#endif