/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 19:59:54 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/04 18:37:11 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_MINISHELL_H
# define MS_MINISHELL_H

# include "libft.h"
# include "ft_bool.h"
# include "ft_printf.h"
# include "ft_type.h"

# include "ms_builtin.h"
# include "ms_env.h"
# include "ms_error.h"
# include "ms_exec.h"
# include "ms_parser.h"
# include "ms_expand.h"

typedef struct s_minishell
{
	t_syntax	syntax;
	t_token		**token;
	t_heredoc	*heredoc;
	t_env		**env;
	t_ast		*ast;
}				t_minishell;

#endif