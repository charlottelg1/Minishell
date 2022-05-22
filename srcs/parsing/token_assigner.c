/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_assigner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 02:58:01 by egiacomi          #+#    #+#             */
/*   Updated: 2022/05/08 19:18:12 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	space_assign(int i, char *phrase, t_token *token, int *token_num)
{
	int	start;

	start = i;
	while (phrase[i + 1] && ft_isspace(phrase[i]))
		i++;
	if (start != 0 && (ft_isarg(phrase[i]) || \
		ft_isquote(phrase[i]) || ft_isredir(phrase[i])))
	{
		token[*token_num].word = ft_substr(phrase, start, 1);
		(*token_num) += 1;
	}
	return (i);
}

int	arg_assign(int i, char *phrase, t_token *token, int *token_num)
{
	int	start;
	int	len;

	start = i;
	while (ft_isarg(phrase[i + 1]))
		i++;
	len = (i + 1) - start;
	token[*token_num].word = ft_substr(phrase, start, len);
	(*token_num) += 1;
	return (i);
}

int	quote_assign(int i, char *phrase, t_token *token, int *token_num)
{
	int	start;
	int	len;
	int	quote;

	start = i;
	quote = phrase[i++];
	while (phrase[i] && phrase[i] != quote)
		i++;
	if (phrase[i] != quote)
		i--;
	len = (i + 1) - start;
	token[*token_num].word = ft_substr(phrase, start, len);
	(*token_num) += 1;
	return (i);
}

int	redir_assign(int i, char *phrase, t_token *token, int *token_num)
{
	int	start;
	int	len;

	start = i;
	if (ft_isredir(phrase[i + 1]))
		i++;
	if (ft_isredir(phrase[i + 1]))
		i++;
	len = (i + 1) - start;
	token[*token_num].word = ft_substr(phrase, start, len);
	(*token_num) += 1;
	while (ft_isspace(phrase[i + 1]))
		i++;
	return (i);
}

void	token_assign(char *phrase, t_token *token)
{
	int	i;
	int	token_num;

	i = -1;
	token_num = 0;
	while (token && phrase && phrase[++i])
	{
		if (ft_isspace(phrase[i]))
			i = space_assign(i, phrase, token, &token_num);
		if (ft_isarg(phrase[i]))
			i = arg_assign(i, phrase, token, &token_num);
		if (ft_isquote(phrase[i]))
			i = quote_assign(i, phrase, token, &token_num);
		if (ft_isredir(phrase[i]))
			i = redir_assign(i, phrase, token, &token_num);
	}
}

/* void	token_assign(char *phrase, t_token *token)
{
	int	i;
	int	start;
	int	len;
	int	token_num;
	int	quote;

	i = -1;
	start = 0;
	token_num = 0;
	while (token && phrase && phrase[++i])
	{
		if (ft_isspace(phrase[i]))
		{
			start = i;
			while (phrase[i + 1] && ft_isspace(phrase[i]))
				i++;
			if (start != 0 && (ft_isarg(phrase[i]) || \
				ft_isarg(phrase[i]) || ft_isredir(phrase[i])))
				token[token_num++].word = ft_substr(phrase, start, 1);
		}
		if (ft_isarg(phrase[i]))
		{
			start = i;
			while (ft_isarg(phrase[i + 1]))
				i++;
			len = (i + 1) - start;
			token[token_num++].word = ft_substr(phrase, start, len);
		}
		if (ft_isquote(phrase[i]))
		{
			start = i;
			quote = phrase[i++];
			while (phrase[i] && phrase[i] != quote)
				i++;
			if (phrase[i] != quote)
				i--;
			len = (i + 1) - start;
			token[token_num++].word = ft_substr(phrase, start, len);
		}
		if (ft_isredir(phrase[i]))
		{
			start = i;
			if (ft_isredir(phrase[i + 1]))
				i++;
			if (ft_isredir(phrase[i + 1]))
				i++;
			len = (i + 1) - start;
			token[token_num++].word = ft_substr(phrase, start, len);
			while (ft_isspace(phrase[i + 1]))
				i++;
		}
	}
} */
