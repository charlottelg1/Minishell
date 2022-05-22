/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:10:30 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/08 23:28:26 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*get_pathname(char **path, char *args)
{
	int		i;
	char	*path_test;
	char	*tmp;

	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		path_test = ft_strjoin(tmp, args);
		free(tmp);
		if (access(path_test, F_OK) == 0)
			return (path_test);
		else
			i++;
		free(path_test);
	}
	return (NULL);
}

int	has_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*find_pathname(char	*args, char **env)
{
	int		i;
	char	**path;
	char	*path_test;

	if (!args)
		return (NULL);
	i = 0;
	if (has_slash(args) == 1 && access(args, F_OK) == 0)
		return (ft_strdup(args));
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	if (!env[i])
		path = NULL;
	else
		path = ft_split(env[i] + 5, ':');
	path_test = get_pathname(path, args);
	if (path)
		free_split(path);
	return (path_test);
}
