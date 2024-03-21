/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:44:20 by jiwojung          #+#    #+#             */
/*   Updated: 2024/03/21 10:25:42 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ms_parser.h"

void	ms_init_syntax(t_syntax *syntax)
{
	syntax->line = NULL;
	syntax->words = NULL;
	syntax->words_cnt = 0;
}
