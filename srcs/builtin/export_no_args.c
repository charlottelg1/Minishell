/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:08:28 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/04 18:15:34 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_quotes(char *str)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	tmp2 = ft_strdup(str);
	if (hasequal(str))
	{
		while (str[i] != '=')
			i++;
		i++;
		if (str[i])
		{
			tmp = ft_substr(str, 0, i);
			free(tmp2);
			tmp2 = ft_freejoin(tmp, ft_strdup("\""));
			tmp2 = ft_freejoin(tmp2, ft_strdup(str + i));
			tmp2 = ft_freejoin(tmp2, ft_strdup("\""));
		}
	}
	return (tmp2);
}

void	free_tablines(char **tab)
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

char	**export_no_args(char **env)
{
	char	**env_sort;
	int		i;
	char	**tab_env;

	(void)env;
	tab_env = lst_to_tab(g_global.cmdline->l_env);
	i = 0;
	while (tab_env[i])
		i++;
	env_sort = ft_calloc(sizeof(char *), (i + 1));
	i = 0;
	while (tab_env[i])
	{
		env_sort[i] = "export ";
		env_sort[i] = ft_strjoin(env_sort[i], tab_env[i]);
		i++;
	}
	env_sort[i] = NULL;
	env_sort = sort_tab(env_sort, i);
	free_tablines(tab_env);
	return (env_sort);
}

int	ret_expnoargs(char **env)
{
	char	**sort_lstenv;

	(void)env;
	sort_lstenv = export_no_args(env);
	display_tab(sort_lstenv);
	free_tablines(sort_lstenv);
	return (0);
}
