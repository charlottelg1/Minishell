/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:11:54 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/04 21:28:52 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_smallenv(char **env)
{
	static char	**tab;
	char		*tmp;

	tab = ft_calloc(sizeof(char *), 4);
	tmp = find_varenv("PWD", env);
	tmp = ft_freejoinsecond("PWD=", tmp);
	tab[0] = ft_strdup(tmp);
	free(tmp);
	tmp = find_varenv("SHLVL", env);
	tmp = ft_freejoinsecond("SHLVL=", tmp);
	tab[1] = ft_strdup(tmp);
	free(tmp);
	tmp = find_varenv("PATH", env);
	tmp = ft_freejoinsecond("PATH=", tmp);
	tab[2] = ft_strdup(tmp);
	tab[3] = NULL;
	free(tmp);
	return (tab);
}

int	hasequal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	display_env(t_env *l_env)
{
	t_env	*tmp;

	tmp = l_env;
	while (tmp)
	{
		if (hasequal(tmp->str))
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
}

int	env_cmd(char **args, t_line cmd, t_bifunct *bifunct)
{
	t_env	*l_env;
	char	*tmp;

	(void)bifunct;
	(void)cmd;
	l_env = g_global.cmdline->l_env;
	if (args[1])
	{
		tmp = ft_strjoin("env: '", args[1]);
		tmp = ft_freejoinfirst(tmp, "': No such file or directory\n");
		ft_putstr_fd(tmp, 2);
		free(tmp);
		return (127);
	}
	display_env(l_env);
	return (0);
}
