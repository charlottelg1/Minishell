/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:37:47 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/09 00:14:26 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nbargs_echo(t_line cmd)
{
	int		i;
	int		j;
	t_token	*words;

	i = 0;
	j = 0;
	words = cmd.word;
	while (j < cmd.word_num)
	{
		if (is_arg(words[j]) || is_space(words[j]))
			i++;
		j++;
	}
	return (i);
}

int	condition_tab_echo(t_line cmd, int i)
{
	if (ft_strlen(cmd.word[i].word) > 0 && \
		(is_arg(cmd.word[i]) || ((is_space(cmd.word[i]) && i != 1 && \
		ft_strlen(cmd.word[i - 1].word) > 0))))
		return (1);
	else if (ft_strlen(cmd.word[i].word) > 0 && \
		(is_arg(cmd.word[i]) || (is_space(cmd.word[i]) && i != 1 && \
		(is_arg(cmd.word[i - 1]) || is_space(cmd.word[i - 1])))))
		return (1);
	else
		return (0);
}

char	**get_tab_cmd_echo(t_line cmd)
{
	int		i;
	int		j;
	char	**args;
	int		nb_args;

	i = -1;
	j = 0;
	nb_args = get_nbargs_echo(cmd);
	args = ft_calloc(nb_args + 1, sizeof(char *));
	while (++i < cmd.word_num)
	{
		if (i == 0 && ft_strlen(cmd.word[i].word) > 0 && \
			(is_arg(cmd.word[i]) || is_space(cmd.word[i])))
			args[j++] = cmd.word[i].word;
		else if (condition_tab_echo(cmd, i))
			args[j++] = cmd.word[i].word;
	}
	args[j] = NULL;
	return (args);
}

int	get_nbargs(t_line cmd)
{
	int		i;
	int		j;
	t_token	*words;

	i = 0;
	j = 0;
	words = cmd.word;
	while (j < cmd.word_num)
	{
		if (is_arg(words[j]))
			i++;
		j++;
	}
	return (i);
}

char	**get_tab_cmd(t_line cmd)
{
	int		i;
	int		j;
	char	**args;
	int		nb_args;

	i = 0;
	j = 0;
	if (!ft_strncmp(cmd.word[0].word, "echo", 5))
		return (get_tab_cmd_echo(cmd));
	nb_args = get_nbargs(cmd);
	args = ft_calloc(nb_args + 1, sizeof(char *));
	while (i < cmd.word_num)
	{
		if (is_arg(cmd.word[i]))
		{
			args[j] = cmd.word[i].word;
			j++;
		}
		i++;
	}
	args[j] = NULL;
	return (args);
}
