/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 15:33:40 by charlottelg       #+#    #+#             */
/*   Updated: 2022/05/11 18:33:40 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//FIXME
//- si ctrl c dans heredoc : open fd et la commande s'execute
//-->peut=etre avec un return precis type -2 ? pour gere ce cas en particulier ?

void	handler_heredoc(int signum)
{
	if (signum == SIGINT)
	{
		g_global.ret = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		close(STDIN_FILENO);
	}
	return ;
}

int	loop_heredoc(char *limitator, int *fd)
{
	char	*str;
	char	*is_limit;

	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		is_limit = ft_strdup(str);
		str = check_expand_heredoc(limitator, str);
		if (ft_strcmp(is_limit, limitator) == 0)
		{
			free(str);
			free(is_limit);
			break ;
		}
		write(fd[1], str, ft_strlen(str));
		write(fd[1], "\n", 1);
		free(str);
		free(is_limit);
	}
	return (0);
}

void	heredoc_child_finish(int *fd, char *limitator, t_env *cpy_env)
{
	int	res;

	res = 0;
	signal(SIGINT, handler_heredoc);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	res = loop_heredoc(limitator, fd);
	if (g_global.ret == 130)
		res = 130;
	close(fd[1]);
	close_stdfileno();
	if (cpy_env)
	{
		cpy_env = free_node(cpy_env);
		free(cpy_env);
	}
	clean_line(g_global.cmdline);
	exit (res);
}

int	ft_heredoc(char *limitator, t_env *cpy_env)
{
	int		fd[2];
	int		pid;
	int		status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	if (pipe(fd) == -1)
	{
		printf("echec creation du pipe heredoc\n");
		return (0);
	}
	pid = ft_fork();
	if (pid == 0)
	{
		heredoc_child_finish(fd, limitator, cpy_env);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if (WEXITSTATUS(status) == 130)
	{
		g_global.ret = 130;
		close(fd[0]);
		return (-1);
	}
	return (fd[0]);
}
