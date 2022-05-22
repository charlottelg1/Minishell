/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:55:02 by giaco             #+#    #+#             */
/*   Updated: 2022/05/01 17:59:50 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_word(t_token *phrase)
{
	t_token	*tmp;
	int		i;

	tmp = phrase;
	i = 0;
	while (tmp && tmp->word)
	{
		printf("token %d is : %s\ntype : %u\n", i, tmp->word, tmp->type);
		i++;
		tmp = tmp->next;
	}
}

void	display_phrase(t_line *cmd)
{
	t_line	*tmp;
	int		i;

	tmp = cmd;
	i = 0;
	while (tmp && tmp->phrase)
	{
		printf("\nphrase %d is : %s\n", i, tmp->phrase);
		display_word(tmp->word);
		printf("\n");
		i++;
		tmp = tmp->next;
	}
}
