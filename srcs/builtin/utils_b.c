/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 16:05:26 by cle-gran          #+#    #+#             */
/*   Updated: 2022/04/30 19:19:40 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_listdup(t_env *l_env)
{
	int		i;
	t_env	*tmp;
	t_env	*ptr;

	i = 0;
	ptr = l_env;
	while (ptr)
	{
		ptr = ptr->next;
		i++;
	}
	tmp = ft_calloc(i, sizeof(t_env));
	if (!tmp)
		return (NULL);
	i = 0;
	while (l_env)
	{
		tmp[i] = *l_env;
		l_env = l_env->next;
		i++;
	}
	return (tmp);
}

char	*join_args(char **av)
{
	char	*args;
	char	*tmp;
	int		i;

	i = 2;
	args = ft_strdup("");
	if (av[2])
	{
		while (av[i])
		{
			tmp = ft_strjoin(args, av[i]);
			free(args);
			args = ft_strdup(tmp);
			free(tmp);
			tmp = ft_strjoin(args, " ");
			free(args);
			args = ft_strdup(tmp);
			free(tmp);
			i++;
		}
	}
	return (args);
}

int	size_list(t_env	*l_env)
{
	int	i;

	i = 0;
	while (l_env[i].next)
		i++;
	return (i);
}

void	lst_cpy(t_env *new, t_env *old, int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		new[j] = old[j];
		j++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 | !s2)
		return (-1);
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
