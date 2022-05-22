/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:06:03 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 17:43:11 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <signal.h>

# include "struct.h"
# include "parsing.h"
# include "builtin.h"
# include "expand.h"
# include "redir.h"
# include "pipex.h"
# include "exec.h"
# include "../libft/srcs/libft.h"

extern t_global	g_global;
void	handler(int signum);
void	handlercmd(int signum);
int		ft_strisspace(char *str);
t_env	*ft_tenvcpy(t_env *l_env, char **env);
int		get_sizelst(t_env *l_env, char **env);
int		ft_strisspace(char *str);
int		get_size_tab(char **env);
char	*ft_freejoinsecond(char *str1, char *str2);

#endif
