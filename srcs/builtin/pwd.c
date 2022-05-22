/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 20:43:31 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 16:25:19 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pwd_args(char *str, t_line cmd)
{
	int		i;
	char	*tmp;
	char	res[2];

	(void)cmd;
	if (!str)
		return (1);
	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i] == 'L' || str[i] == 'P')
		i++;
	if (str[i] == ' ')
		return (0);
	else
	{
		res[0] = str[i];
		res[1] = '\0';
		tmp = ft_strjoin("pwd: -", res);
		tmp = ft_freejoinfirst(tmp, ": invalid option\npwd: usage: pwd [-LP]\n");
		ft_putstr_fd(tmp, STDERR_FILENO);
		free(tmp);
		return (2);
	}
	return (0);
}

int	pwd_cmd(char **args, t_line cmd, t_bifunct *bifunct)
{
	char	current[4096];
	int		ret;
	int		i;

	(void)bifunct;
	(void)cmd;
	i = 1;
	ret = 0;
	while (args[i])
	{
		ret = check_pwd_args(args[i], cmd);
		i++;
	}
	if (ret == 0)
	{
		if (getcwd(current, sizeof(current)) != NULL)
			printf("%s\n", current);
		else
			return (-1);
	}
	return (ret);
}
