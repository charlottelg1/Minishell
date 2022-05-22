/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:03:53 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/09 00:15:55 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_has_n(char **args, int i)
{
	int	j;

	j = 0;
	if (args[i][j] == '-' && args[i][j + 1] == 'n')
	{
		j++;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			return (-1);
	}
	else
		return (-1);
	return (j);
}

int	is_opt_n(char **args)
{
	int	i;
	int	space;

	i = 0;
	space = 0;
	args++;
	while (args[i])
	{
		if (ft_strisspace(args[i]) && args[i + 1] && \
		(echo_has_n(args, i + 1) != -1 || echo_has_n(args, i - 1) != -1))
			i++;
		else
		{
			if (echo_has_n(args, i) == -1)
				break ;
			i++;
		}
	}
	return (i);
}

char	*ft_freejoinfirst(char *str1, char *str2)
{
	char	*res;

	res = ft_strjoin(str1, str2);
	free(str1);
	return (res);
}

char	**get_line_echo(int *n, char **args)
{
	int	len;

	len = 0;
	*n = is_opt_n(args);
	return (args);
}

int	echo_cmd(char **args, t_line cmd, t_bifunct *bifunct)
{
	int		n;
	int		i;

	(void)bifunct;
	(void)cmd;
	n = 0;
	get_line_echo(&n, args);
	args += n;
	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
