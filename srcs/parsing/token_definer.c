/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_definer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 03:39:51 by egiacomi          #+#    #+#             */
/*   Updated: 2022/05/09 00:14:53 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_merger(int next, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	if (tmp && tmp->word)
	{
		while (tmp->next && is_arg(*tmp->next))
		{
			token->word = ft_freejoinfirst(token->word, tmp->next->word);
			tmp->next->word = ft_freedup(tmp->next->word, "");
			tmp->next->type = IS_SPACE;
			tmp = tmp->next;
			next++;
		}
	}
	return (next);
}

void	token_merging(t_token *token)
{
	t_token	*tmp;
	int		next;

	tmp = token;
	while (tmp && tmp->word)
	{
		next = 1;
		if (tmp->next)
		{
			if (tmp->word[0] == '$' && ft_strlen(tmp->word) == 1 && \
				(tmp->next->type == ARG_DQ || tmp->next->type == ARG_SQ))
				tmp->word = ft_freedup(tmp->word, "");
			if (is_arg(*tmp) && is_arg(*tmp->next))
				next = token_merger(next, tmp);
		}
		while (next-- > 0)
			tmp = tmp->next;
	}
}

void	token_expand_first(t_token *tmp, char **env)
{
	tmp->word = expanser(tmp->word, env);
	if (tmp->word == NULL)
		tmp->type = NONE;
}

void	token_expanding(t_token *token, char **env)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->word)
	{
		if (tmp->prev)
		{
			if (is_expandable(tmp) && tmp->prev->type != HERE_DOC)
			{
				tmp->word = expanser(tmp->word, env);
				if (ft_strlen(tmp->word) == 0)
					tmp->type = NONE;
			}
			else if (tmp->prev->type == HERE_DOC)
			{
				while (tmp->next && tmp->next->type != IS_SPACE)
					tmp = tmp->next;
			}
		}
		else if (is_expandable(tmp))
			token_expand_first(tmp, env);
		tmp = tmp->next;
	}
}

void	define_type(t_token *token, char **env, t_env *cpy_env)
{
	t_token	*tmp;
	int		prev_type;

	tmp = token;
	while (tmp && tmp->word)
	{
		if (tmp->prev)
			prev_type = tmp->prev->type;
		if (ft_isspace(tmp->word[0]))
			tmp->type = IS_SPACE;
		if (ft_isarg(tmp->word[0]))
			tmp->type = ARG;
		if (ft_isredir(tmp->word[0]))
			define_redir(tmp);
		if (ft_isquote(tmp->word[0]))
			define_quote(tmp);
		tmp = tmp->next;
	}
	token_expanding(token, env);
	token_merging(token);
	define_file(token, cpy_env);
}

/* void	define_type(t_token *token, char **env, t_env *cpy_env)
{
	t_token	*tmp;
	int		prev_type;

	tmp = token;
	while (tmp && tmp->word)
	{
		if (tmp->prev)
			prev_type = tmp->prev->type;
		if (ft_isspace(tmp->word[0]))
			tmp->type = IS_SPACE;
		if (ft_isarg(tmp->word[0]))
			tmp->type = ARG;
		if (ft_isredir(tmp->word[0]))
			define_redir(tmp);
		if (ft_isquote(tmp->word[0]))
		{
			if (tmp->word[0] == 39)
				tmp->type = ARG_SQ;
			else
				tmp->type = ARG_DQ;
			tmp->word = del_quote(tmp->word);
		}
		if (is_expandable(tmp) && prev_type != HERE_DOC)
			tmp->word = expanser(tmp->word, env);
		tmp = tmp->next;
	}
	define_file(token, cpy_env);
} */

/* int	filer(t_token *tmp, t_env *cpy_env, char *limitor)
{
	int	next;

	next = 1;
	if (tmp->type == FILE_IN)
		tmp->next->type = OPEN_FILE;
	if (tmp->type == FILE_OUT)
		tmp->next->type = EXIT_FILE;
	if (tmp->type == HERE_DOC)
	{
		tmp->next->type = LIMITOR;
		limitor = merge_limitor_args(&next, tmp->next);
		tmp->next->fdin = ft_heredoc(limitor, cpy_env);
	}
	if (tmp->type == FILE_OUT_SUR)
		tmp->next->type = EXIT_FILE_RET;
	return (next);
}

void	define_file(t_token *token, t_env *cpy_env)
{
	t_token	*tmp;
	int		next;
	char	*limitor;

	tmp = token;
	limitor = NULL;
	while (tmp && tmp->word)
	{
		if (tmp->next)
			next = filer(tmp, cpy_env, limitor);
		while (next-- > 0)
		{
			if (tmp->next == NULL)
			{
				tmp = 0;
				break;
			}
			tmp = tmp->next;
		}
	}
} */
