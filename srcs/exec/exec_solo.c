/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:44:13 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 18:37:27 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		printf("echec fork\n");
		return (-1);
	}
	return (pid);
}

int	execve_solo(char **args, int *redir, int *savestd)
{
	int		pid;
	char	*pathname;
	int		status;
	char	**new_env;

	pid = ft_fork();
	signal(SIGINT, handlercmd);
	signal(SIGQUIT, handlercmd);
	if (pid == 0)
	{
		new_env = lenv_to_env(g_global.cmdline->l_env);
		pathname = find_pathname(args[0], new_env);
		if (pathname)
		{
			if (access(pathname, F_OK) == 0)
				execve_go(savestd, pathname, args, new_env);
			msg_cmdnotfound(args[0], savestd);
		}
		else
			msg_cmdnotfound(args[0], savestd);
		clean_exec_solo(redir, savestd, pathname, new_env);
		exit (127);
	}
	wait(&status);
	return (WEXITSTATUS(status));
}

int	exec_solo(t_line *cmdline)
{
	char	**args;
	int		ret;

	cmdline->savestd[0] = dup(STDIN_FILENO);
	cmdline->savestd[1] = dup(STDOUT_FILENO);
	cmdline->redir[0] = redirect_solo_in(cmdline);
	cmdline->redir[1] = redirect_solo_out(cmdline);
	if (cmdline->redir[0] == -1 || cmdline->redir[1] == -1)
	{
		std_backup(cmdline->redir, cmdline->savestd);
		if (g_global.ret == 130)
			return (130);
		return (1);
	}
	args = cmdline->args;
	ret = 0;
	if (cmdline->redir[0] != -1)
	{
		if (is_builtin(args))
			ret = exec_builtin(args, *cmdline);
		else
			ret = execve_solo(args, cmdline->redir, cmdline->savestd);
	}
	std_backup(cmdline->redir, cmdline->savestd);
	return (ret);
}

int	redirect_solo_out(t_line *cmd)
{
	int	nb_redout;
	int	fdout;

	fdout = 1;
	nb_redout = check_redirout(cmd);
	if (nb_redout > 0)
	{
		fdout = is_redirout(cmd, nb_redout);
		dup2(fdout, STDOUT_FILENO);
		if (fdout != 1)
			close(fdout);
	}
	return (fdout);
}

int	redirect_solo_in(t_line *cmd)
{
	int	nb_redin;
	int	fdin;

	fdin = 0;
	nb_redin = check_redirin(cmd);
	if (nb_redin > 0)
	{
		fdin = is_redirin(cmd, nb_redin);
		dup2(fdin, STDIN_FILENO);
		if (fdin > 0)
			close(fdin);
	}
	return (fdin);
}
