/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 15:47:11 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 20:31:52 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

int		exec_solo(t_line *cmdline);
int		ft_fork(void);
void	handlercmd(int signum);
void	clean_exec_solo(int *redir, int *savestd, char *pathname, char \
**new_env);

#endif
