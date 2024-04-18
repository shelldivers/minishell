/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_macro2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwojung <jiwojung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 21:35:27 by jiwojung          #+#    #+#             */
/*   Updated: 2024/04/15 20:30:20 by jiwojung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ms_error_bonus.h"
#include "ms_exec_bonus.h"
#include <unistd.h>
#include <sys/stat.h>

int	s_isdir(int m)
{
	return (((m) & S_IFMT) == S_IFDIR);
}
