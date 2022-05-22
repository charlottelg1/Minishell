/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 16:55:20 by giaco             #+#    #+#             */
/*   Updated: 2022/04/27 18:29:02 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(int c)
{
	if (((signed)c == 34 || (signed)c == 39))
		return (TRUE);
	return (FALSE);
}

int	ft_isspace(int c)
{
	if (((signed)c >= 9 && (signed)c <= 13) || (signed)c == 32)
		return (TRUE);
	return (FALSE);
}

int	ft_isredir(int c)
{
	if (((signed)c == 60 || (signed)c == 62))
		return (TRUE);
	return (FALSE);
}

int	ft_isarg(int c)
{
	if (ft_isprint(c) && !ft_isredir(c) && !ft_isquote(c) && !ft_isspace(c))
		return (TRUE);
	return (FALSE);
}

int	ft_isenv(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c) || c == 95)
		return (TRUE);
	return (FALSE);
}
