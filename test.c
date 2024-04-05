#include "ms_minishell.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

t_bool	ms_find_close_quote(char *word, int idx)
{
	char	quote;
	size_t	i;

	i = idx;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			quote = word[i];
			while (word[i] && word[i] != quote)
				i++;
			if (!word[i])
				return (FALSE);
			return (TRUE);
		}
	}
	return (FALSE);
}

char	*ms_quote_removal(char *word, size_t i, size_t j)
{
	char	quote;
	char	*new_word;

	new_word = (char *)malloc(sizeof(char) * (ft_strlen(word) + 1));
	if (!new_word)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '\"')
		{
			quote = word[i];
			if (ms_find_close_quote(word, i) == TRUE)
			{
				i++;
				while (word[i] && word[i] != quote)
					new_word[j++] = word[i++];
				i++;
			}
		}
		else
			new_word[j++] = word[i++];
	}
	return (new_word);
}

int	main(int argc, char **argv)
{
	while (1)
	{
		char	*line = readline("Enter a string: ");
		printf ("line = %s\n", line);
		char	*removed = ms_quote_removal(line, 0, 0);
		printf("ms_quote_removal: %s\n", removed);
		free(line);
		free(removed);
	}
}
