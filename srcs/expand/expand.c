/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:26:49 by charlottelg       #+#    #+#             */
/*   Updated: 2022/05/07 18:56:52 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*getijexp(int *i, int *j, char *str, char *fstr)
{
	*j = *i;
	*i = index_doll(str, *i);
	if (*i != *j)
		fstr = ft_addexp(str, *i, *j, fstr);
	if (str[*i])
		*i += 1;
	return (fstr);
}

char	*ft_expand(char *str, char **env)
{
	int		i;
	int		j;
	char	*fstr;
	char	*tmp;

	fstr = ft_strdup("");
	i = 0;
	j = 0;
	while (str[i])
	{
		fstr = getijexp(&i, &j, str, fstr);
		if (str[i] && str[i - 1] == '$')
		{
			if (ft_isdigit(str[i]))
				i++;
			else if (ft_isalpha(str[i]) || str[i] == '?')
			{
				tmp = get_varenv(str, &i, &j, env);
				fstr = ft_freejoin(fstr, tmp);
			}
		}
		else if (str[i] == '\0' && str[i - 1] == '$')
			fstr = ft_freejoinfirst(fstr, "$");
	}
	return (fstr);
}

char	**lenv_to_env(t_env	*l_env)
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
		tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	*expanser(char *str, char **env)
{
	char	*expand;
	char	**new_env;

	(void)env;
	new_env = lenv_to_env(g_global.cmdline->l_env);
	expand = ft_expand(str, new_env);
	free(str);
	free_tablines(new_env);
	return (expand);
}
