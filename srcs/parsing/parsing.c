/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:46:41 by giaco             #+#    #+#             */
/*   Updated: 2022/05/12 19:21:56 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_line *cmd)
{
	t_token	*token;
	int		args_num;

	token = cmd->word;
	args_num = 0;
	while (token)
	{
		if (token->type == ARG || token->type == ARG_DQ || token->type == \
		ARG_SQ)
			args_num++;
		token = token->next;
	}
	return (args_num);
}

void	indent_args(t_line *cmdline)
{
	t_line	*tmp_cmd;

	tmp_cmd = cmdline;
	while (tmp_cmd)
	{
		tmp_cmd->args = get_tab_cmd(*tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
}

int	to_consider(char *str, int i)
{
	int	j;
	int	count_singleq;
	int	count_doubleq;
	int	count_esc;

	j = -1;
	count_singleq = 0;
	count_doubleq = 0;
	count_esc = 0;
	while (str && ++j < i)
	{
		if (str[j] == 39 && (count_doubleq % 2) == 0)
			count_singleq++;
		if (str[j] == 34 && (count_singleq % 2) == 0)
			count_doubleq++;
	}
	if (str[i] == 39 && (count_singleq % 2) != 0)
		count_singleq++;	
	if (str[i] == 34 && (count_doubleq % 2) != 0)
		count_doubleq++;
	while (j > 0 && str[--j] == 92)
		count_esc++;
	if ((count_singleq % 2) != 0 || (count_doubleq % 2) != 0 || \
	(count_esc % 2) != 0)
		return (FALSE);
	return (TRUE);
}

void	add_lenv(t_env *l_env, char **env)
{
	t_line	*tmp;
	t_env	*tmp_env;

	tmp = g_global.cmdline;
	if (!l_env)
	{
		tmp_env = env_to_list(g_global.cmdline->env);
		tmp->l_env = tmp_env;
	}
	else
		tmp->l_env = ft_tenvcpy(l_env, env);
}

t_line	*parsing(char *prompt, char **env, int ret, t_env *l_env)
{
	int		phrase_count;
	int		piped;

	phrase_count = phrase_counter(prompt);
	g_global.cmdline = create_line(phrase_count, env, prompt, ret);
	add_lenv(l_env, env);
	piped = piper(prompt, g_global.cmdline);
	tokenizer(g_global.cmdline, l_env);
	if (!piped || check_error(prompt))
	{
		clean_line(g_global.cmdline);
		return (NULL);
	}
	indent_args(g_global.cmdline);
	if (l_env)
	{
		l_env = free_node(l_env);
		free(l_env);
		l_env = NULL;
	}
	l_env = g_global.cmdline->l_env;
	return (g_global.cmdline);
}
