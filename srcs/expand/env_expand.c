/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:11:15 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 17:49:41 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_varenv(char *str, char **env)
{
	int		i;
	int		j;
	char	*res;

	res = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == str[j])
			j++;
		if (str[j] == '\0' && env[i][j] == '=')
		{
			j++;
			res = ft_strdup(env[i] + j);
			return (res);
		}
		i++;
	}
	return (res);
}

char	*get_varenv(char *str, int *i, int *j, char **env)
{
	char	*var;
	char	*tmp;

	if (str[*i] == '?')
	{
		var = ft_itoa(g_global.ret);
		*i += 1;
	}
	else
	{
		*i = get_endalnu(str, *i, j);
		tmp = ft_substr(str, *j, *i - *j);
		var = find_varenv(tmp, env);
		free(tmp);
		if (!var)
			var = ft_strdup("");
	}
	return (var);
}
