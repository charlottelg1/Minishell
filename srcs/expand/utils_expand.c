/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:10:24 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 17:44:21 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_freejoin(char *str1, char *str2)
{
	char	*joined;

	joined = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (joined);
}

int	get_endalnu(char *str, int i, int *j)
{
	*j = i;
	if (ft_isalpha(str[i]))
		while (ft_isalnum(str[i]) || (str[i] > 47 && str[i] < 57) || \
		(str[i] > 64))
			i++;
	return (i);
}

char	*ft_addexp(char *str, int i, int j, char *fstr)
{
	char	*tmp;

	tmp = ft_substr(str, j, i - j);
	fstr = ft_freejoin(fstr, tmp);
	return (fstr);
}

int	digit_at(char *str, int i)
{
	if (ft_isdigit(str[i]) || str[i] == '@')
		i ++;
	return (i);
}

int	index_doll(char *str, int i)
{
	char	c;

	if (!str[i])
		return (0);
	while (str[i] && str[i] != '$')
		i++;
	if (str[i])
	{
		if (str[i + 1])
		{
			c = str[i + 1];
			if ((c == 37 || c == 43 || c == 46 || c == 47 || c == 58 || \
			c == 61))
				i += 2;
		}
	}
	return (i);
}
