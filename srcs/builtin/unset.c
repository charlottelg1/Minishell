/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 19:38:25 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/08 21:20:46 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*remove_env(t_env *tmp, char **tab_args, int i)
{
	int	j;

	j = 0;
	while (tmp->str[j] && tab_args[i][j] && tmp->str[j] == \
	tab_args[i][j])
		j++;
	if (tab_args[i][j] == '\0' && (tmp->str[j] == '=' || !tmp->str[j]))
	{
		if (tmp->previous)
			tmp->previous->next = tmp->next;
		else if (tmp->next)
			tmp->next->previous = NULL;
		if (tmp->next)
			tmp->next->previous = tmp->previous;
		else if (tmp->previous)
			tmp->previous->next = NULL;
		free(tmp->str);
	}
	tmp = tmp->next;
	return (tmp);
}

int	unset_cmd(char **args, t_line cmd, t_bifunct *bifunct)
{
	int		i;
	t_env	*tmp;
	t_env	*l_env;
	int		ret;

	(void)bifunct;
	l_env = g_global.cmdline->l_env;
	i = 0;
	tmp = l_env;
	ret = 0;
	while (args[i])
	{
		if (ret == 0)
			ret = valid_arg(args[i], cmd);
		while (tmp)
			tmp = remove_env(tmp, args, i);
		tmp = l_env;
		i++;
	}
	return (ret);
}
