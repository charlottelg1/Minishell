/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 23:27:55 by giaco             #+#    #+#             */
/*   Updated: 2022/05/07 17:51:47 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	phrase_counter(char *str)
{
	int	i;
	int	phrase_count;

	phrase_count = 1;
	i = -1;
	while (str && str[++i])
	{
		if (str[i] == '|')
		{
			if (to_consider(str, i))
				phrase_count++;
		}
	}
	return (phrase_count);
}

int	check_pipe_parse_error(char *line)
{
	int	i;

	i = 0;
	if (line)
	{
		while (ft_isspace(line[i]))
			i++;
		if (line[i] == '|')
		{
			printf("syntax error near unexpected token `|'\n");
			return (TRUE);
		}
	}
	while (line[i])
	{
		if (pipe_parse_error(line, i))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	piper(char *line, t_line *cmdline)
{
	int				i;
	unsigned int	start;
	int				cmd_num;

	i = -1;
	start = 0;
	cmd_num = 0;
	if (check_pipe_parse_error(line))
		return (FALSE);
	while (line && line[++i])
	{
		if (line[i] == '|')
		{
			if (to_consider(line, i))
			{
				cmdline[cmd_num].phrase = ft_substr(line, start, i - start);
				start = i + 1;
				cmd_num++;
			}
		}
		if (line[i + 1] == '\0' && line[i] != '|')
			cmdline[cmd_num].phrase = ft_substr(line, start, i - start + 1);
	}
	return (TRUE);
}

/* int	piper(char *line, t_line *cmdline)
{
	int				i;
	unsigned int	start;
	int				len;
	int				cmd_num;

	i = -1;
	start = 0;
	cmd_num = 0;
	if (check_pipe_parse_error(line))
		return (FALSE);
	while (line && line[++i])
	{
		if (line[i] == '|')
		{
			if (to_consider(line, i))
			{
				len = i - start;
				cmdline[cmd_num].phrase = ft_substr(line, start, len);
				start = i + 1;
				cmd_num++;
			}
		}
		if (line[i + 1] == '\0' && line[i] != '|')
		{
			len = i - start + 1;
			cmdline[cmd_num].phrase = ft_substr(line, start, len);
		}
	}
	return (TRUE) ;
} */
