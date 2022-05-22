/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 14:57:09 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/12 20:16:43 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex_builtin(char **args, t_line cmd)
{
	int	ret;

	ret = exec_builtin(args, cmd);
	std_backup(cmd.redir, cmd.savestd);
	close_stdfileno();
	return (ret);
}

int	pipex_exec(int fdin, int fdout, t_line cmd, int i)
{
	char	*pathname;
	int		ret;
	char	**args;
	char	**new_env;

	ret = redirection(fdin, fdout, &cmd);
	args = g_global.cmdline[i].args;
	if (cmd.redir[0] != -1 && cmd.redir[1] != -1)
	{
		if (is_builtin(g_global.cmdline[i].args))
			return (pipex_builtin(g_global.cmdline[i].args, cmd));
		new_env = lenv_to_env(g_global.cmdline->l_env);
		pathname = find_pathname(g_global.cmdline[i].args[0], \
		new_env);
		if (pathname)
		{
			if (access(pathname, F_OK) == 0)
				execve_go(cmd.savestd, pathname, args, new_env);
		}
		ret = cmd_not_found(g_global.cmdline[i].args, cmd.redir, cmd.savestd);
		free(pathname);
		free_tablines(new_env);
	}
	return (ret);
}

void	exec_child(int **pipes, int i, int nb_cmd, int *pids)
{
	int	ret;

	ret = 0;
	signal(SIGINT, handlercmd);
	signal(SIGQUIT, handlercmd);
	close_pipes_child(pipes, i, nb_cmd);
	if (i == 0)
	{
		close(pipes[i][0]);
		ret = pipex_exec(STDIN_FILENO, pipes[i + 1][1], g_global.cmdline[i], i);
	}
	else if (i == nb_cmd - 1)
	{
		close(pipes[nb_cmd][1]);
		ret = pipex_exec(pipes[i][0], STDOUT_FILENO, g_global.cmdline[i], i);
	}
	else
		ret = pipex_exec(pipes[i][0], pipes[i + 1][1], g_global.cmdline[i], i);
	clean_pipes_child(pids, pipes, nb_cmd);
	if (i != nb_cmd - 1)
		ret = 0;
	exit (ret);
}

int	pipex(t_line *cmdline)
{
	int		nb_cmd;
	int		*pids;
	int		**pipes;
	int		i;

	nb_cmd = get_nbcmd(cmdline);
	pids = ft_calloc(sizeof(int), nb_cmd);
	pipes = pipes_init(nb_cmd);
	i = 0;
	while (i < nb_cmd)
	{
		pids[i] = ft_fork();
		close(pipes[nb_cmd][0]);
		close(pipes[0][1]);
		if (pids[i] == -1)
			return (0);
		if (pids[i] == 0)
			exec_child(pipes, i, nb_cmd, pids);
		i++;
	}
	clean_parent(pipes, nb_cmd, pids);
	return (0);
}
