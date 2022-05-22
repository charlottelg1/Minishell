/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 17:47:33 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/04 20:14:21 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path_home(char **env)
{
	char	*path;

	path = find_varenv("HOME", env);
	return (path);
}

int	cd_args(char **args, t_line cmd)
{
	char	*tmp;

	(void)cmd;
	if (args[2])
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(args[1]) == -1)
	{
		tmp = ft_strjoin("cd: ", args[1]);
		tmp = ft_freejoinfirst(tmp, ": No such file or directory\n");
		ft_putstr_fd(tmp, STDERR_FILENO);
		free(tmp);
		return (1);
	}
	return (0);
}

int	cd_cmd(char **args, t_line cmd, t_bifunct *bifunct)
{
	char	*path_home;
	char	**env;
	t_env	*l_env;
	int		ret;

	(void)bifunct;
	l_env = g_global.cmdline->l_env;
	env = g_global.cmdline->env;
	ret = 0;
	if (!args[1])
	{
		path_home = get_path_home(env);
		chdir(path_home);
		free(path_home);
		return (ret);
	}
	else
		ret = cd_args(args, cmd);
	change_env_cd(l_env);
	return (ret);
}
