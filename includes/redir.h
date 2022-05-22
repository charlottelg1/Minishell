/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:54:51 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 14:33:11 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "minishell.h"

int		redirection(int fdin, int fdout, t_line *cmd);
int		redirect_in(int fdin, t_line *cmd);
int		redirect_out(int fdout, t_line *cmd);
int		check_redirin(t_line *cmd);
int		check_redirout(t_line *cmd);
int		is_redirin(t_line *cmd, int nb_redin);
int		is_redirout(t_line *cmd, int nb_redout);
int		chev_g(t_token word);
int		chev_d(t_token word);
int		double_chev_d(t_token word);
int		redirect_solo_out(t_line *cmd);
int		redirect_solo_in(t_line *cmd);
void	std_backup(int *redir, int *savestd);
void	close_stdfileno(void);
char	*check_expand_heredoc(char *limitator, char *str);
// void	display_fd(int *fd, int nbfd);

char	*merge_limitor_args(int	*next, t_token *token);
int		ft_heredoc(char *limitator, t_env *cpy_env);
int		add_fd_cmd(char *limitator);
void	handler_heredoc(int signum);

#endif
