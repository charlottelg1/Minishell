/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 19:54:39 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 18:35:01 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_in(int fdin, t_line *cmd)
{
	int	nb_redin;

	cmd->savestd[0] = dup(STDIN_FILENO);
	nb_redin = check_redirin(cmd);
	if (nb_redin)
	{
		fdin = is_redirin(cmd, nb_redin);
		dup2(fdin, STDIN_FILENO);
	}
	else
		dup2(fdin, STDIN_FILENO);
	if (fdin > 0)
		close(fdin);
	return (fdin);
}

int	check_redirin(t_line *cmd)
{
	int		i;
	int		j;
	t_token	*word;

	i = 0;
	j = 0;
	word = cmd->word;
	while (i < cmd->word_num)
	{
		if (word[i].type == FILE_IN || word[i].type == HERE_DOC)
			j++;
		i++;
	}
	return (j);
}

void	close_fdj(int nb_redin, int *fd, int *i)
{
	int	j;

	j = 0;
	while (j < nb_redin - 1)
	{
		if (fd[j] == -1)
			break ;
		close(fd[j++]);
	}
	*i = fd[j];
	free(fd);
}

int	is_redirin(t_line *cmd, int nb_redin)
{
	int		*fd;
	int		i;
	int		j;
	t_token	*word;

	i = 0;
	j = -1;
	word = cmd->word;
	fd = ft_calloc(sizeof(int), nb_redin);
	while (i < cmd->word_num)
	{
		if (word[i].type == HERE_DOC)
			fd[++j] = word[i + 1].fdin;
		if (word[i].type == FILE_IN)
		{
			fd[++j] = chev_g(word[i + 1]);
			if (fd[j] == -1)
				break ;
		}
		i++;
	}
	close_fdj(nb_redin, fd, &i);
	return (i);
}
