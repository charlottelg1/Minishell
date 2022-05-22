/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirout.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:52:44 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/10 22:57:11 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_out(int fdout, t_line *cmd)
{
	int	nb_redout;

	cmd->savestd[1] = dup(STDOUT_FILENO);
	nb_redout = check_redirout(cmd);
	if (nb_redout)
	{
		fdout = is_redirout(cmd, nb_redout);
		dup2(fdout, STDOUT_FILENO);
	}
	else
		dup2(fdout, STDOUT_FILENO);
	if (fdout != 1)
		close(fdout);
	return (fdout);
}

int	check_redirout(t_line *cmd)
{
	int		i;
	int		j;
	t_token	*word;

	i = 0;
	j = 0;
	word = cmd->word;
	while (i < cmd->word_num)
	{
		if (word[i].type == FILE_OUT || word[i].type == FILE_OUT_SUR)
			j++;
		i++;
	}
	return (j);
}

int	is_redirout(t_line *cmd, int nb_redout)
{
	int		*fd;
	int		i;
	int		j;
	t_token	*word;

	i = 0;
	j = 0;
	word = cmd->word;
	fd = ft_calloc(sizeof(int), nb_redout);
	while (i < cmd->word_num)
	{
		if (word[i].type == FILE_OUT)
			fd[j++] = chev_d(word[i + 1]);
		else if (word[i].type == FILE_OUT_SUR)
			fd[j++] = double_chev_d(word[i + 1]);
		i++;
	}
	j = 0;
	while (j < nb_redout - 1)
		close(fd[j++]);
	i = fd[j];
	free(fd);
	return (i);
}
