/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_definer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 20:30:20 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/08 15:28:18 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	define_redir(t_token *tmp)
{
	if (ft_strlen(tmp->word) == 1)
	{
		if (tmp->word[0] == '<')
			tmp->type = FILE_IN;
		else
			tmp->type = FILE_OUT;
	}
	if (ft_strlen(tmp->word) == 2)
	{
		if (tmp->word[0] == '<' && tmp->word[1] == '<')
			tmp->type = HERE_DOC;
		else if (tmp->word[0] == '>' && tmp->word[1] == '>')
			tmp->type = FILE_OUT_SUR;
		else
			tmp->type = WRONG_REDIR;
	}
	if (ft_strlen(tmp->word) == 3)
			tmp->type = WRONG_REDIR;
}

void	define_file(t_token *token, t_env *cpy_env)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->word)
	{
		if (tmp->next)
		{
			if (tmp->type == FILE_IN)
				tmp->next->type = OPEN_FILE;
			if (tmp->type == FILE_OUT)
				tmp->next->type = EXIT_FILE;
			if (tmp->type == HERE_DOC)
			{
				tmp->next->type = LIMITOR;
				tmp->next->fdin = ft_heredoc(tmp->next->word, cpy_env);
			}
			if (tmp->type == FILE_OUT_SUR)
				tmp->next->type = EXIT_FILE_RET;
		}
			tmp = tmp->next;
	}
}

void	define_quote(t_token *tmp)
{
	if (tmp->word[0] == 39)
		tmp->type = ARG_SQ;
	else
		tmp->type = ARG_DQ;
	tmp->word = del_quote(tmp->word);
}

char	*ft_freedup(char *str_free, char *str)
{
	char	*new_str;

	new_str = ft_strdup(str);
	free(str_free);
	return (new_str);
}
