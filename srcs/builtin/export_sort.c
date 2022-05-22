/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 17:22:28 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/04 18:15:37 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap_str(char **s1, char **s2)
{
	char	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

char	**sort_tab(char **env_sort, int len)
{
	int	i;

	i = 0;
	while (i < len && env_sort[i + 1])
	{
		if (ft_strcmp(env_sort[i], env_sort[i + 1]) > 0)
		{
			ft_swap_str(&env_sort[i], &env_sort[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	return (env_sort);
}

char	**lst_to_tab(t_env	*l_env)
{
	int		nb;
	int		i;
	char	**tab;
	t_env	*tmp;

	nb = get_sizelst(l_env, g_global.cmdline->env);
	i = 0;
	tab = ft_calloc(sizeof(char *), nb + 1);
	tmp = l_env;
	while (i < nb)
	{
		tab[i] = get_quotes(tmp->str);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}
