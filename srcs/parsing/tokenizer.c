/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 14:49:11 by giaco             #+#    #+#             */
/*   Updated: 2022/05/08 11:53:12 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer(t_line *cmdline, t_env *cpy_env)
{
	t_line	*tmp;
	int		i;

	tmp = cmdline;
	i = 0;
	while (tmp && tmp->phrase)
	{
		tmp->word_num = word_counter(tmp->phrase);
		tmp->word = create_token(tmp->word_num);
		token_assign(tmp->phrase, tmp->word);
		define_type(tmp->word, cmdline->env, cpy_env);
		i++;
		tmp = tmp->next;
	}
}
