/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_solo_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 20:27:55 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/10 23:36:01 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_stdfileno(void)
{
	close(STDOUT_FILENO);
	close(STDIN_FILENO);
	close(STDERR_FILENO);
}

void	msg_cmdnotfound(char *args, int *savestd)
{
	char	*tmp;

	(void)savestd;
	tmp = ft_strjoin(args, ": command not found \n");
	ft_putstr_fd(tmp, STDERR_FILENO);
	free(tmp);
}

void	clean_exec_solo(int *redir, int *savestd, char *pathname, \
char **new_env)
{
	std_backup(redir, savestd);
	close_stdfileno();
	if (pathname)
		free(pathname);
	clean_line(g_global.cmdline);
	free_tablines(new_env);
}

int	tab_space_count(char **args)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (args[i])
	{
		if (!ft_strisspace(args[i]))
			words++;
		i++;
	}
	return (words);
}

char	**tab_nospace(char **args)
{
	int		i;
	int		words;
	char	**tab;
	int		j;

	tab = NULL;
	words = tab_space_count(args);
	if (words != 0)
		tab = ft_calloc(sizeof(char *), words + 1);
	i = 0;
	j = 0;
	while (i < words)
	{
		if (!ft_strisspace(args[i]))
		{
			tab[j] = ft_strdup(args[i]);
			j++;
		}
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
