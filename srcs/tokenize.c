#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "minishell.h"

/*==================LIBFT_START===========================*/

static size_t	ft_strlen(const char *s)
{
	size_t	cnt;

	cnt = 0;
	while (s[cnt] != '\0')
		cnt++;
	return (cnt);
}

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_;
	const unsigned char	*src_;
	size_t				i;

	if (dst == 0 && src == 0)
		return (0);
	dst_ = (unsigned char *)dst;
	src_ = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_[i] = src_[i];
		i++;
	}
	return (dst);
}

static char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	s1_len;

	s1_len = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (!str)
		return (0);
	str[s1_len] = '\0';
	ft_memcpy(str, s1, s1_len);
	return (str);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (len == 0 || start > s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	ft_memcpy(str, s + start, len);
	return (str);
}

static size_t	ft_strcmp(char *dst, const char *src)
{
	while (*dst && *src && *dst == *src)
	{
		dst++;
		src++;
	}
	if (*dst == *src)
		return (0);
	return (1);
}

/*==================LIBFT_END===========================*/

/*================tokenize.c_START================*/

//token  AND_IF    OR_IF    PIPE    LBRACE    RBRACE
/*      '&&'      '||'     '|'       '('       ')'    */


//token  DLESS  DGREAT   DREAD  DWRITE
/*      '<<'   '>>'     '<'     '>'    */

static t_token	*new_token(char *value)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(1);
	token->value = ft_strdup(value);
	if (ft_strcmp(value, "&&") == 0)
		token->type = AND_IF;
	else if (ft_strcmp(value, "||") == 0)
		token->type = OR_IF;
	else if (ft_strcmp(value, "|") == 0)
		token->type = PIPE;
	else if (value[0] == '(' && value[ft_strlen(value) - 1] == ')')
		token->type = SUBSHELL;
	else if (ft_strcmp(value, "<<") == 0)
		token->type = DLESS;
	else if (ft_strcmp(value, ">>") == 0)
		token->type = DGREAT;
	else if (ft_strcmp(value, "<") == 0)
		token->type = DREAD;
	else if (ft_strcmp(value, ">") == 0)
		token->type = DWRITE;
	else
		token->type = WORD;
	return (token);
}

t_token	**tokenize(t_syntax *syntax)
{
	int		i;
	t_token	**token;

	token = (t_token **)malloc(sizeof(t_token *) * (syntax->words_cnt + 1));
	if (!token)
		exit (1);
	i = 0;
	while (i < syntax->words_cnt)
	{
		token[i] = new_token(syntax->words[i]);
		i++;
	}
	token[i] = NULL;
	return (token);
}

/*================tokenize.c_END================*/
