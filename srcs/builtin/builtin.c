/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:24:29 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/10 23:36:33 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bifunct	*init_bifunct(t_bifunct *bifunct)
{
	bifunct[0].cmd = "echo";
	bifunct[0].pf = &echo_cmd;
	bifunct[1].cmd = "cd";
	bifunct[1].pf = &cd_cmd;
	bifunct[2].cmd = "pwd";
	bifunct[2].pf = &pwd_cmd;
	bifunct[3].cmd = "export";
	bifunct[3].pf = &export_cmd;
	bifunct[4].cmd = "unset";
	bifunct[4].pf = &unset_cmd;
	bifunct[5].cmd = "env";
	bifunct[5].pf = &env_cmd;
	bifunct[6].cmd = "exit";
	bifunct[6].pf = exit_cmd;
	bifunct[7].cmd = "/usr/bin/echo";
	bifunct[7].pf = &echo_cmd;
	bifunct[8].cmd = "/usr/bin/pwd";
	bifunct[8].pf = &pwd_cmd;
	bifunct[9].cmd = "/usr/bin/env";
	bifunct[9].pf = &env_cmd;
	return (bifunct);
}

int	exec_builtin(char **args, t_line cmd)
{
	t_bifunct	*bifunct;
	int			i;
	int			ret;

	i = 0;
	bifunct = (t_bifunct *)ft_calloc(10, sizeof(t_bifunct));
	bifunct = init_bifunct(bifunct);
	while (i < 10)
	{
		if (ft_strcmp(args[0], bifunct[i].cmd) == 0)
		{
			ret = bifunct[i].pf(args, cmd, bifunct);
			free(bifunct);
			g_global.ret = ret;
			return (ret);
		}
		i++;
	}
	free(bifunct);
	return (-1);
}

int	is_builtin(char **args)
{
	t_bifunct	*bifunct;
	int			i;

	i = 0;
	bifunct = (t_bifunct *)ft_calloc(10, sizeof(t_bifunct));
	bifunct = init_bifunct(bifunct);
	while (i < 10)
	{
		if (ft_strcmp(args[0], bifunct[i].cmd) == 0)
		{
			free(bifunct);
			return (1);
		}
		i++;
	}
	free(bifunct);
	return (0);
}
