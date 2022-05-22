/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initclose_pipex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:04:39 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 15:49:46 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes_child(int **pipes, int i, int nb)
{
	int	j;

	j = 0;
	while (j <= nb)
	{
		if (i != j)
			close(pipes[j][0]);
		if (i + 1 != j)
			close(pipes[j][1]);
		j++;
	}
}

void	wait_parent(int nb_cmd)
{
	int	i;
	int	status;
	int	ret;

	i = 0;
	ret = 0;
	while (i < nb_cmd)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) != 0)
			ret = WEXITSTATUS(status);
		i++;
	}
	g_global.ret = ret;
}

void	clean_parent(int **pipes, int nb, int *pids)
{
	int	i;

	i = 0;
	while (i <= nb)
	{
		if (i != nb)
			close(pipes[i][0]);
		if (i != 0)
			close(pipes[i][1]);
		i++;
	}
	wait_parent(nb);
	clean_pipes_parent(pipes, nb, pids);
}

/* void	clean_parent(int **pipes, int nb, int *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i <= nb)
	{
		if (i != nb)
			close(pipes[i][0]);
		if (i != 0)
			close(pipes[i][1]);
		if (i < nb)
			waitpid(-1, &status, 0);
		i++;
	}
	g_global.ret = WEXITSTATUS(status);
	clean_pipes_parent(pipes, nb, pids);
} */

void	free_pipes(int **pipes, int nb)
{
	int	i;

	i = 0;
	while (i <= nb)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**pipes_init(int nb_cmd)
{
	int	i;
	int	**pipes;

	i = 0;
	pipes = ft_calloc(sizeof(int *), nb_cmd + 1);
	while (i <= nb_cmd)
	{
		pipes[i] = ft_calloc(sizeof(int), 2);
		i++;
	}
	i = 0;
	while (i <= nb_cmd)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("echec creation du pipe %d\n", i);
			return (0);
		}
		i++;
	}
	return (pipes);
}
