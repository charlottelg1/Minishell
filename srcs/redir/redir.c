/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:34:01 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 18:31:57 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 	int fd = open("f2", O_WRONLY); ft_putstr_fd("coucou redir\n", fd);close(fd);
// TODO : cmd : ``` >/'' ``` should only say / is a directory
void	std_backup(int *redir, int *savestd)
{
	if (redir[1] != 1)
		dup2(savestd[1], STDOUT_FILENO);
	if (redir[0] != 0)
		dup2(savestd[0], STDIN_FILENO);
	close(savestd[1]);
	close(savestd[0]);
}

int	redirection(int fdin, int fdout, t_line *cmd)
{
	cmd->redir[0] = redirect_in(fdin, cmd);
	cmd->redir[1] = redirect_out(fdout, cmd);
	if (cmd->redir[0] == -1 || cmd->redir[1] == -1)
	{
		std_backup(cmd->redir, cmd->savestd);
		close_stdfileno();
		if (g_global.ret == 130)
			return (130);
		return (1);
	}
	return (127);
}

int	chev_d(t_token word)
{
	int		fdout;

	fdout = open(word.word, O_WRONLY | O_CREAT | O_TRUNC, 00777);
	if (fdout == -1)
		printf("%s: Can't write on file\n", word.word);
	return (fdout);
}

int	double_chev_d(t_token word)
{
	int		fdout;

	fdout = open(word.word, O_WRONLY | O_CREAT | O_APPEND, 00777);
	if (fdout == -1)
		printf("%s: Can't write on file\n", word.word);
	return (fdout);
}

int	chev_g(t_token word)
{
	int	fdin;

	fdin = open(word.word, O_RDONLY);
	if (fdin == -1)
		printf("%s: No such file or directory\n", word.word);
	return (fdin);
}

// void	display_fd(int *fd, int nbfd)
// {
// 	int	i;

// 	i = 0;
// 	while (i < nbfd)
// 	{
// 		printf("fd[%d] is %d\n", i, fd[i]);
// 		i++;
// 	}
// }

/* TODO : for HEREDOC int	chev_g(t_token word)
{
	int	fdin;

	fdin = ft_atoi(word.word)
	if (fdin == -1)
		printf("%s: No such file or directory\n", word.word);
	return (fdin);
} */
