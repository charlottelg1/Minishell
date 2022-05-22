/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 17:28:46 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 13:51:33 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_size_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

int	get_sizelst(t_env *l_env, char **env)
{
	t_env	*tmp;
	int		i;

	if (l_env == NULL)
	{
		i = get_size_tab(env);
		return (i);
	}
	else
	{
		i = 0;
		tmp = l_env;
		if (tmp && tmp->next)
		{
			while (tmp)
			{
				tmp = tmp->next;
				i++;
			}
		}
	}
	return (i);
}

t_env	*fill_tmplenv(t_env *tmp, t_env *templenv, int size, int *i)
{
	t_env	*prev;

	prev = NULL;
	while (templenv)
	{
		tmp[*i].str = ft_strdup(templenv->str);
		tmp[*i].type = 0;
		tmp[*i].size = size;
		tmp[*i].previous = prev;
		if (*i != size)
			tmp[*i].next = &tmp[*i + 1];
		prev = &tmp[*i];
		*i += 1;
		templenv = templenv->next;
	}
	return (tmp);
}

t_env	*ft_tenvcpy(t_env *l_env, char **env)
{
	t_env	*tmp;
	int		i;
	int		size;
	t_env	*templenv;

	i = 0;
	if (l_env)
		size = get_sizelst(l_env, env);
	else
		size = get_size_tab(env);
	tmp = ft_calloc(sizeof(t_env), size);
	if (l_env)
	{
		templenv = l_env;
		tmp = fill_tmplenv(tmp, templenv, size, &i);
		tmp[i - 1].next = NULL;
	}
	else if (env)
		tmp = env_to_list(env);
	else
		tmp = NULL;
	return (tmp);
}
