/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:59:54 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 20:27:59 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MINISHELL_BONUS_H
# define MS_MINISHELL_BONUS_H
# include "ms_parser_bonus.h"
# include "ms_env_bonus.h"

typedef struct s_minishell
{
	struct s_syntax	syntax;
	struct s_token	**token;
	struct s_env	**env;
	struct s_ast	*ast;
}				t_minishell;

void	ms_clear_all(t_minishell *shell);

#endif
