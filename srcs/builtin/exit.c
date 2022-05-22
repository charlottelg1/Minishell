/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:31:15 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/12 20:13:05 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_longlong_exit(char *exit_arg)
{
	char	*tmp;
	

	if (exit_arg[0] == '-')
	{
		if (ft_strlen(exit_arg) > 20)
		{
			tmp = ft_strjoin("exit\nexit: ", exit_arg);
			tmp = ft_freejoinfirst(tmp, ": numeric argument required\n");
			ft_putstr_fd(tmp, 2);
			free(tmp);
			return (TRUE);
		}
	}
	else
	{
		if (ft_strlen(exit_arg) > 19)
		{
			tmp = ft_strjoin("exit\nexit: ", exit_arg);
			tmp = ft_freejoinfirst(tmp, ": numeric argument required\n");
			ft_putstr_fd(tmp, 2);
			free(tmp);
			return (TRUE);
		}
	}
	return (FALSE);
}

int	check_exit_args(char **args, t_line cmd)
{
	int		i;
	char	*tmp;

	(void)cmd;
	i = 0;
	if (args[1][0] == '-')
		i++;
	while (args[1][i])
	{		
		if (!ft_isdigit(args[1][i]))
		{
			tmp = ft_strjoin("exit\nexit: ", args[1]);
			tmp = ft_freejoinfirst(tmp, ": numeric argument required\n");
			ft_putstr_fd(tmp, 2);
			free(tmp);
			return (2);
		}
		i++;
	}
	if (args[2])
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		return (1);
	}
	else
	{
		if (check_longlong_exit(args[1]))
			return (2);	
		i = ft_atoi(args[1]);
	}
	return (i);
}

int	exit_cmd(char **args, t_line cmd, t_bifunct *bifunct)
{
	int	ret;

	(void)cmd;
	ret = 0;
	if (args[1])
		ret = check_exit_args(args, cmd);
	if (!g_global.cmdline->next)
	{
		if (ret != 1)
		{
			if (ret != 2)
				ft_putstr_fd("exit\n", cmd.savestd[1]);
			std_backup(g_global.cmdline->redir, g_global.cmdline->savestd);
			if (get_size_tab(g_global.cmdline->env) == 3)
				free_tablines(g_global.cmdline->env);
			clean_line(g_global.cmdline);
			free(bifunct);
			exit (ret);
		}
	}
	return (ret);
}
