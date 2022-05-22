/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:32:21 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 15:40:19 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
		g_global.ret = 130;
	}
	return ;
}

void	handlercmd(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		write(1, "\n", 1);
		rl_replace_line("", 0);
		g_global.ret = 130;
	}
	if (signum == SIGQUIT)
	{
		g_global.ret = 131;
		ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
	}
	return ;
}

int	ft_strisspace(char *str)
{
	int	i;

	if (!str)
		return (1);
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

char	*ft_freejoinsecond(char *str1, char *str2)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	free(str2);
	return (res);
}
