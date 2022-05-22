/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 19:19:27 by giaco             #+#    #+#             */
/*   Updated: 2022/05/08 16:36:22 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_token	*create_token(int word_num)
{
	t_token	*new_words;
	int		i;

	i = -1;
	new_words = NULL;
	if (word_num)
	{
		new_words = (t_token *)ft_calloc(word_num, sizeof(t_token));
		if (!new_words)
			return (NULL);
		while (++i < word_num)
		{
			new_words[i].word = NULL;
			new_words[i].word = NULL;
			new_words[i].type = NONE;
			if (i < word_num - 1)
				new_words[i].next = &new_words[i + 1];
			else
				new_words[i].next = NULL;
		}
	}
	return (new_words);
} */

t_token	*create_token(int word_num)
{
	t_token	*new_words;
	int		i;

	i = -1;
	new_words = NULL;
	if (word_num)
	{
		new_words = (t_token *)ft_calloc(word_num, sizeof(t_token));
		if (!new_words)
			return (NULL);
		while (++i < word_num)
		{
			if (i == 0)
				new_words[i].prev = NULL;
			else
				new_words[i].prev = &new_words[i - 1];
			new_words[i].word = NULL;
			new_words[i].type = NONE;
			if (i < word_num - 1)
				new_words[i].next = &new_words[i + 1];
			else
				new_words[i].next = NULL;
		}
	}
	return (new_words);
}

t_line	*create_line(int nb_cmd, char **env, char *prompt, int ret)
{
	t_line	*new_line;
	int		i;

	i = -1;
	new_line = (t_line *)ft_calloc(nb_cmd, sizeof(t_line));
	if (!new_line)
		return (NULL);
	while (++i < nb_cmd)
	{
		new_line[i].prompt = prompt;
		new_line[i].phrase = NULL;
		new_line[i].word = NULL;
		new_line[i].word_num = 0;
		new_line[i].args = NULL;
		new_line[i].env = env;
		new_line[i].ret = ret;
		new_line[i].redir[0] = 0;
		new_line[i].redir[1] = 0;
		if (i < nb_cmd - 1)
			new_line[i].next = &new_line[i + 1];
		else
			new_line[i].next = NULL;
	}
	return (new_line);
}

t_env	*free_node(t_env *l_env)
{
	t_env	*tmp;
	t_env	*tofree;
	t_env	*prev;

	tmp = l_env;
	prev = NULL;
	while (tmp)
	{
		free(tmp->str);
		if (tmp && tmp->type == 1)
		{
			tofree = tmp;
			if (prev)
				prev->next = tmp->next;
			tmp = tmp->next;
			free(tofree);
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (l_env);
}

void	total_freezing(t_line	*freezer)
{
	int	i;

	i = 0;
	if (freezer->phrase)
		free(freezer->phrase);
	if (freezer->word)
	{
		while (i < freezer->word_num)
		{
			if (freezer->word[i].fdin)
				close(freezer->word[i].fdin);
			free(freezer->word[i++].word);
		}
		free(freezer->word);
	}
	if (freezer->args)
		free(freezer->args);
	freezer = freezer->next;
}

void	clean_line(t_line *cmdline)
{
	t_line	*freezer;

	freezer = cmdline;
	if (freezer->l_env)
	{
		freezer->l_env = free_node(freezer->l_env);
		free(freezer->l_env);
	}
	freezer->l_env = NULL;
	while (freezer)
	{
		total_freezing(freezer);
		freezer = freezer->next;
	}
	free(cmdline);
	cmdline = NULL;
}

/* int	*init_fd_heredoc(t_line *g_cmdline)
{
	int		*tab;
	int		i;
	char	*prompt;
	int		nb;

	i = 0;
	nb = 0;
	tab = NULL;
	prompt = cmdline->prompt;
	if (prompt)
	{
		while (prompt[i + 1])
		{
			if (to_consider(prompt, i) && (prompt[i] == '<' && prompt[i + 1] == '<'))
			{
				if (prompt[i + 2] && (ft_isredir(prompt[i + 2]) == FALSE))
					nb++;
			}
			i++;
		}
	}
	// printf("there are %d here_doc boloss\n", nb);
	if (nb)
		tab = (int *)ft_calloc(nb, sizeof(int));
	return (tab);
}
 */

/* void	clean_line(t_line *cmdline)
{
	t_line	*freezer;
	int		i;

	freezer = cmdline;
	if (freezer->l_env)
	{
		freezer->l_env = free_node(freezer->l_env);
		free(freezer->l_env);
	}
	freezer->l_env = NULL;
	while (freezer)
	{
		i = 0;
		if (freezer->phrase)
			free(freezer->phrase);
		if (freezer->word)
		{
			while (i < freezer->word_num)
			{
				if (freezer->word[i].fdin)
					close(freezer->word[i].fdin);
				free(freezer->word[i++].word);
			}
			free(freezer->word);
		}
		if (freezer->args)
			free(freezer->args);
		freezer = freezer->next;
	}
	free(cmdline);
	cmdline = NULL;
} */
