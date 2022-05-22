/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:00:43 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 15:46:51 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "minishell.h"

int		pipex(t_line *cmdline);
char	**get_tab_cmd(t_line cmd);
void	init_pipes(int **pipes, int nb);
void	close_pipes_child(int **pipes, int i, int nb);
void	clean_parent(int **pipes, int nb, int *pids);
int		get_nbargs(t_line cmd);
int		is_arg(t_token	word);
int		get_nbcmd(t_line *cmd);
char	*find_pathname(char	*args, char **env);
void	exec_child(int **pipes, int i, int nb_cmd, int *pids);
void	clean_pipes_child(int *pids, int **pipes, int nb_cmd);
void	clean_pipes_parent(int **pipes, int nb_cmd, int *pids);
void	free_pipes(int **pipes, int nb);
int		**pipes_init(int nb_cmd);
int		cmd_not_found(char **args, int *redir, int *savestd);
void	wait_parent(int nb_cmd);
void	close_stdfileno(void);
void	msg_cmdnotfound(char *args, int *savestd);
char	**tab_nospace(char **args);
void	free_split(char	**tab);
int		get_nbargs_echo(t_line cmd);
char	**get_tab_cmd_echo(t_line cmd);
int		get_nbargs(t_line cmd);
char	**get_tab_cmd(t_line cmd);
int		is_space(t_token	word);
int		is_arg(t_token	word);
int		get_nbcmd(t_line *cmd);
void	display_args(char **args, int nb);
void	execve_go(int *savestd, char *pathname, char **args, char **new_env);

#endif
