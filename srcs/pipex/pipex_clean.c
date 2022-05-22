/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:18:48 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/10 21:43:36 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_pipes_parent(int **pipes, int nb_cmd, int *pids)
{
	close(pipes[nb_cmd][1]);
	close(pipes[0][0]);
	free(pids);
	free_pipes(pipes, nb_cmd);
}

void	close_pipes(int	**pipes, int nb_cmd)
{
	int	i;

	i = 0;
	while (i <= nb_cmd)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	clean_pipes_child(int *pids, int **pipes, int nb_cmd)
{
	close_pipes(pipes, nb_cmd);
	free(pids);
	free_pipes(pipes, nb_cmd);
	clean_line(g_global.cmdline);
}

// l. 40 et 38 on intervertit ? 