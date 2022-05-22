/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 19:31:03 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/08 13:02:13 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_quote(char *phrase, int i, int *word_num)
{
	int	quote;

	quote = phrase[i++];
	while (phrase[i] && phrase[i] != quote)
		i++;
	if (phrase[i] != quote)
		i--;
	(*word_num)++;
	return (i);
}

int	word_not_space(char *phrase, int i, int *word_num)
{
	if (ft_isarg(phrase[i]))
	{
		(*word_num)++;
		while (ft_isarg(phrase[i + 1]))
			i++;
	}
	if (ft_isquote(phrase[i]))
		i = word_quote(phrase, i, word_num);
	if (ft_isredir(phrase[i]))
	{
		if (ft_isredir(phrase[i + 1]))
			i++;
		if (ft_isredir(phrase[i + 1]))
			i++;
		(*word_num)++;
		while (ft_isspace(phrase[i + 1]))
			i++;
	}
	return (i);
}

int	word_counter(char *phrase)
{
	int	word_num;
	int	i;

	i = -1;
	word_num = 0;
	while (phrase && phrase[++i])
	{
		if (ft_isspace(phrase[i]))
		{
			word_num++;
			while (phrase[i + 1] && ft_isspace(phrase[i]))
			{
				if (i == 0)
					word_num--;
				i++;
			}
			if (ft_isspace(phrase[i]) && phrase[i + 1] == '\0')
			{
				word_num--;
				break ;
			}
		}
		i = word_not_space(phrase, i, &word_num);
	}
	return (word_num);
}

char	*del_quote(char *word)
{
	char	*new_word;
	int		len;

	len = ft_strlen(word);
	new_word = ft_substr(word, 1, len - 2);
	free(word);
	return (new_word);
}

int	is_expandable(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	if (token->type == ARG || token->type == ARG_DQ)
	{
		str = token->word;
		while (str[i])
		{
			if (str[i] == '$')
			{
				if (ft_isalnum(str[i + 1]) || str[i + 1] == 95 \
					|| str[i + 1] == '?' || str[i + 1] == '\0')
					return (TRUE);
			}
			i++;
		}
	}
	return (FALSE);
}
