/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:21:32 by giaco             #+#    #+#             */
/*   Updated: 2022/05/12 19:22:09 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_parse_error(char *str, int i)
{
	if (ft_isredir(str[i]) && to_consider(str, i))
	{
		if (redir_not_existing(str, &i))
			return (TRUE);
		while (ft_isspace(str[++i]))
		{
			if (ft_isredir(str[i + 1]))
			{
				print_redir_parse_error(str, i);
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

int	pipe_misplaced(char *str, int i)
{
	if (str[i] == '|' && to_consider(str, i))
	{
		if (str[i + 1] == '|')
		{
			printf("syntax error : double pipe not handled\n");
			return (TRUE);
		}
		while (ft_isspace(str[++i]))
		{
			if (str[i + 1] == '|')
			{
				printf("syntax error near unexpected token `%c'\n", str[i + 1]);
				return (TRUE);
			}
		}
	}
	return (FALSE);
}

int	pipe_parse_error(char *str, int i)
{
	if (ft_isredir(str[i]))
	{
		if (str[i + 1] == '|')
		{
			printf("syntax error near unexpected token `%c'\n", str[i + 1]);
			return (TRUE);
		}
		while (ft_isspace(str[++i]))
		{
			if (str[i + 1] == '|')
			{
				printf("syntax error near unexpected token `%c'\n", str[i + 1]);
				return (TRUE);
			}
		}
	}
	if (pipe_misplaced(str, i))
		return (TRUE);
	return (FALSE);
}

int	eol_error(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (ft_isspace(str[i]) || ft_isredir(str[i]) || str[i] == '|')
	{
		if (str[i] == '|')
		{
			printf("syntax error : empty pipe\n");
			return (TRUE);
		}
		if (ft_isredir(str[i]))
		{
			printf("syntax error near unexpected token `newline'\n");
			return (TRUE);
		}
		i--;
	}
	return (FALSE);
}

int	check_error(char *str)
{
	int	i;
	int	count_singleq;
	int	count_doubleq;

	i = 0;
	count_singleq = 0;
	count_doubleq = 0;
	while (str && str[i])
	{
		if (str[i] == 39 && to_consider(str, i))
			count_singleq++;
		if (str[i] == 34 && to_consider(str, i))
			count_doubleq++;
		if (redir_parse_error(str, i))
			return (TRUE);
		i++;
	}
	if (eol_error(str))
		return (TRUE);
	if ((count_singleq % 2) != 0 || (count_doubleq % 2) != 0)
	{
		printf("syntax error : unclosed quote\n");
		return (TRUE);
	}
	return (FALSE);
}
