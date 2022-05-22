/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:50:24 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 18:59:13 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_expand_heredoc(char *limitator, char *str)
{
	char	*str_exp;
	int		i;
	int		count;

	i = -1;
	count = 0;
	(void)limitator;
	if (str[0] == 39 && str[ft_strlen(str) - 1] == 39)
		return (str);
	while (str[++i])
	{
		if (str[i] == '$')
		{
			count++;
			break ;
		}
	}
	if (count > 0)
	{
		str_exp = expanser(str, g_global.cmdline->env);
		return (str_exp);
	}
	else
		return (str);
}
