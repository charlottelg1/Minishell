/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 18:03:24 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 17:04:03 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	l_env_new_node(t_env *l_env, char *str)
{
	t_env	*tmp;
	t_env	*node;

	tmp = l_env;
	node = ft_calloc(sizeof(t_env), 1);
	node->str = ft_strdup(str);
	node->type = 1;
	while (tmp && tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	node->previous = tmp;
	node->next = NULL;
}
