/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ret.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 20:00:30 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 17:44:04 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isexpandret(char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (str[i])
			{
				if (str[i] == '?')
					ret++;
			}
		}
		if (str[i])
			i++;
	}
	return (ret);
}

char	*get_strfinale(char *prev, char *next)
{
	char	*strfinale;
	char	*exp;

	strfinale = NULL;
	exp = ft_itoa(g_global.cmdline->ret);
	if (prev && !ft_strisspace(prev))
		strfinale = ft_strjoin(prev, exp);
	if (next && !ft_strisspace(next))
	{
		if (prev && !ft_strisspace(prev))
			strfinale = ft_freejoinfirst(strfinale, next);
		else
			strfinale = ft_strjoin(exp, next);
	}
	free(prev);
	free(next);
	if (strfinale)
	{
		free(exp);
		return (strfinale);
	}
	return (exp);
}

char	*get_tabexpandret(char *str)
{
	int		i;
	char	*prev;
	char	*next;
	char	*strfinale;

	i = 0;
	next = NULL;
	prev = NULL;
	while (str[i])
	{
		while (str[i] && str[i] != '$')
			i++;
		if (str[i] == '$')
			i++;
		if (str[i] == '?')
		{
			prev = ft_substr(str, 0, i - 1);
			if (ft_isexpandret(str) == 1)
				next = ft_substr(str, i + 1, ft_strlen(str) - i);
			break ;
		}
	}
	strfinale = get_strfinale(prev, next);
	return (strfinale);
}

char	*tab_to_strexp(char **tab)
{
	char	*line;
	char	*tmp;
	int		i;

	if (!tab)
		return (NULL);
	i = 0;
	line = ft_strdup("");
	tmp = ft_strdup("");
	while (tab[i])
	{
		free(tmp);
		line = ft_freejoinfirst(line, tab[i]);
		tmp = ft_strdup(line);
		free(line);
		line = ft_strdup(tmp);
		i++;
	}
	free (tmp);
	return (line);
}

char	*expand_ret(char *str)
{
	int		i;
	int		j;
	int		nb;
	char	**tab;
	char	*strfinale;

	i = 0;
	nb = ft_isexpandret(str);
	if (nb == 0)
		return (str);
	tab = ft_calloc(sizeof(char *), nb + 1);
	j = 0;
	while (i < nb)
	{
		tab[i] = get_tabexpandret(str + j);
		while (str[j] && str[j] != '$')
			j++;
		j += 2;
		i++;
	}
	tab[i] = NULL;
	strfinale = tab_to_strexp(tab);
	free(str);
	free(tab);
	return (strfinale);
}
