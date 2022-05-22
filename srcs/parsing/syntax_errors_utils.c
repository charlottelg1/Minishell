/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:26:39 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/12 19:22:03 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_parse_error(char *str, int i)
{
	i++;
	if (ft_isredir(str[i + 1]))
	{
		if (str[i] == str[i + 1])
		{
			printf("syntax error near unexpected token `%c%c'\n", \
				str[i], str[i + 1]);
			return ;
		}
	}
	printf("syntax error near unexpected token `%c'\n", str[i]);
}

int	redir_not_existing(char *str, int *i)
{
	if (ft_isredir(*(str + (*i + 1))))
	{
		if (*(str + *i) != *(str + (*i + 1)))
		{
			printf("syntax error near unexpected token `%c'\n", *(str + \
			(*i + 1)));
			return (TRUE);
		}
		*i += 1;
		if (ft_isredir(*(str + (*i + 1))))
		{
			print_redir_parse_error(str, *i);
			return (TRUE);
		}
	}
	return (FALSE);
}
