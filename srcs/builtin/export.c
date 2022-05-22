/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 16:34:04 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/08 21:19:29 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(char **tab)
{
	int	i;
	int	j;
	int	valid;

	i = 0;
	valid = 0;
	while (tab[i])
	{
		j = 0;
		if (ft_isdigit(tab[i][j]))
			i++;
		else
		{
			while (ft_isalnum(tab[i][j]) || tab[i][j] == '_')
				j++;
			if (caract_ok_export(tab[i][j]))
				i++;
			else
			{
				valid += 1;
				i++;
			}
		}
	}
	return (valid);
}

int	valid_arg(char *str, t_line cmd)
{
	int		i;

	i = 0;
	if (ft_isdigit(str[i]) || str[i] == '=')
	{
		msg_valid_id(str, cmd);
		return (1);
	}
	else
	{
		while (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		if ((str[i] >= 33 && str[i] <= 47) || str[i] == 58 || str[i] == 63 \
		|| str[i] == 64)
		{
			msg_valid_id(str, cmd);
			return (1);
		}
	}
	return (0);
}

char	*check_punctexport(char	*str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (str[i] == '=' && str[i + 1] == '\0')
	{
		str = ft_strjoin(str, "\b\"");
		return (str);
	}
	if (str[i] == ';' && str[i + 1] == '\0')
	{
		str = ft_substr(str, 0, i);
		return (str);
	}
	return (str);
}

int	proceed_export(char **args, t_env *l_env, t_line cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (args[i])
	{
		ret = valid_arg(args[i], cmd);
		if (ret == 0)
		{
			args[i] = check_punctexport(args[i]);
			var_exist(args[i]);
			l_env_new_node(l_env, args[i]);
		}
		i++;
	}
	return (ret);
}

int	export_cmd(char **args, t_line cmd, t_bifunct *bifunct)
{
	t_env	*l_env;
	char	**env;
	int		ret;

	(void)bifunct;
	l_env = g_global.cmdline->l_env;
	env = g_global.cmdline->env;
	if (!args[1])
		return (ret_expnoargs(env));
	args++;
	ret = proceed_export(args, l_env, cmd);
	return (ret);
}
