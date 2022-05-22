/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:05:46 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 15:46:36 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_go(int *savestd, char *pathname, char **args, char **new_env)
{
	close(savestd[0]);
	close(savestd[1]);
	execve(pathname, args, new_env);
}

int	get_nbcmd(t_line *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	is_arg(t_token word)
{
	if (word.type == ARG || word.type == ARG_SQ || word.type == ARG_DQ)
		return (1);
	return (0);
}

int	is_space(t_token word)
{
	if (word.type == IS_SPACE)
		return (1);
	return (0);
}

int	cmd_not_found(char **args, int *redir, int *savestd)
{
	char	*tmp;

	(void)redir;
	(void)savestd;
	tmp = ft_strjoin(args[0], ": command not found \n");
	ft_putstr_fd(tmp, STDERR_FILENO);
	std_backup(redir, savestd);
	close_stdfileno();
	free(tmp);
	return (127);
}
