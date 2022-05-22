/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:08:22 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 18:02:33 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_envexport(t_env	*tmp)
{
	t_env	*prev;
	t_env	*next;

	prev = tmp->previous;
	next = tmp->next;
	if (prev)
		prev->next = next;
	if (next)
		next->previous = prev;
	free(tmp->str);
	if (tmp->type == 1)
		free(tmp);
}

char	*get_varindexport(int *i, char *var)
{
	char	*str;

	if (hasequal(var))
	{
		while (var[*i] != '=' && var[*i] != '\0')
			*i += 1;
		str = ft_substr(var, 0, *i);
	}
	else
	{
		str = ft_strdup(var);
		*i = ft_strlen(var);
	}
	return (str);
}

int	var_exist(char *var)
{
	t_env	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = g_global.cmdline->l_env;
	str = get_varindexport(&i, var);
	while (tmp)
	{
		if (ft_strncmp(str, tmp->str, i) == 0)
		{
			if (tmp->str[i] == '\0' || tmp->str[i] == '=')
			{
				remove_envexport(tmp);
				free(str);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	free(str);
	return (0);
}

int	caract_ok_export(char c)
{
	if (c == '\0' && c != '=' && c != '+')
		return (1);
	return (0);
}

void	msg_valid_id(char *str, t_line cmd)
{
	char	*tmp;

	(void)cmd;
	tmp = ft_strjoin("export: '", str);
	tmp = ft_freejoinfirst(tmp, "': not a valid identifier\n");
	ft_putstr_fd(tmp, STDERR_FILENO);
	free(tmp);
}
