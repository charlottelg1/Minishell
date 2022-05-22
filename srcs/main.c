/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 14:58:17 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/11 16:09:52 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

t_env	*ctrld(t_env *l_env)
{
	printf("exit\n");
	rl_clear_history();
	if (l_env)
	{
		l_env = free_node(l_env);
		free(l_env);
		l_env = NULL;
	}
	return (l_env);
}

t_env	*execution(t_line *cmdline, int *ret, char **env)
{
	t_env	*l_env;

	if (cmdline->next)
		pipex(cmdline);
	else
		g_global.ret = exec_solo(cmdline);
	*ret = g_global.ret;
	l_env = ft_tenvcpy(cmdline->l_env, env);
	clean_line(cmdline);
	return (l_env);
}

t_env	*loop(t_env *l_env, char **env)
{
	char	*prompt;
	int		ret;

	ret = 0;
	while (1)
	{
		prompt = readline("Prompt> ");
		if (!ft_strisspace(prompt))
		{
			if (prompt)
				add_history(prompt);
			g_global.cmdline = parsing(prompt, env, ret, l_env);
			signal(SIGINT, handlercmd);
			signal(SIGQUIT, handlercmd);
			if (g_global.cmdline)
				l_env = execution(g_global.cmdline, &ret, env);
			signal(SIGINT, handler);
			signal(SIGQUIT, SIG_IGN);
		}
		else if (!prompt)
			return (ctrld(l_env));
	}
	return (l_env);
}

int	main(int ac, char **av, char **env)
{
	t_env	*l_env;

	g_global.ret = 0;
	g_global.cmdline = NULL;
	(void)av;
	l_env = NULL;
	if (ac == 3 && ft_strcmp(av[1], "env") == 0 && ft_strcmp(av[2], "-i") == 0)
	{
		env = get_smallenv(env);
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		l_env = loop(l_env, env);
	}
	else if (ac == 1)
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		l_env = loop(l_env, env);
	}
	if (l_env)
		free(l_env);
	if (get_size_tab(env) == 3)
		free_tablines(env);
	return (0);
}
