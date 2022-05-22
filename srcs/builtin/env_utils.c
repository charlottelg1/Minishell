/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:04:57 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/06 18:43:50 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_gofront(t_env *lst)
{
	while (lst && lst->previous)
		lst = lst->previous;
}

void	lst_goback(t_env *lst)
{
	while (lst && lst->next)
		lst = lst->next;
}

t_env	*l_env_malloc(int nb)
{
	t_env	*l_env;

	if (!nb)
		l_env = ft_calloc(1, sizeof(t_env));
	else
		l_env = ft_calloc(nb, sizeof(t_env));
	return (l_env);
}

// C'est quoi l_env.type ?
t_env	*l_env_fill(t_env *l_env, char **env, int i)
{
	t_env	*tmp;
	int		j;

	j = 0;
	tmp = NULL;
	while (env[j] && j < i)
	{
		l_env[j].previous = tmp;
		l_env[j].type = 0;
		l_env[j].str = ft_strdup(env[j]);
		if (env[j + 1])
			l_env[j].next = &l_env[j + 1];
		else
			l_env[j].next = NULL;
		tmp = &l_env[j];
		j++;
	}
	return (l_env);
}

t_env	*env_to_list(char **env)
{
	int		i;
	t_env	*l_env;

	i = 0;
	while (env[i])
		i++;
	l_env = l_env_malloc(i);
	l_env = l_env_fill(l_env, env, i);
	return (l_env);
}
