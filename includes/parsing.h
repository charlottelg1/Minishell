/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiacomi <egiacomi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:02:16 by giaco             #+#    #+#             */
/*   Updated: 2022/05/08 15:28:02 by egiacomi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/* PARSING */
t_line	*parsing(char *prompt, char **env, int ret, t_env *l_env);
int		to_consider(char *str, int i);
void	indent_args(t_line *cmdline);
int		count_args(t_line *cmd);

/* SYNTAX ERRORS */
int		check_error(char *str);
int		redir_parse_error(char *str, int i);
int		redir_not_existing(char *str, int *i);
void	print_redir_parse_error(char *str, int i);
int		esper_parse_error(char *str, int i);
int		pipe_parse_error(char *str, int i);
int		eol_error(char *str);

/* PIPER */
int		piper(char *line, t_line *cmdline);
int		phrase_counter(char *str);

/* TOKENIZER */
void	token_assign(char *phrase, t_token *token);
void	tokenizer(t_line *cmdline, t_env *cpy_env);
int		word_counter(char *phrase);
void	define_type(t_token *token, char **env, t_env *cpy_env);
void	define_redir(t_token *tmp);
void	define_quote(t_token *tmp);
void	define_file(t_token *token, t_env *cpy_env);
char	*del_quote(char *word);
int		is_expandable(t_token *token);

/* STRCTURE MANAGER */
t_line	*create_line(int nb_cmd, char **env, char *prompt, int ret);
t_env	*free_node(t_env *l_env);
t_token	*create_token(int word_num);
void	clean_line(t_line *cmdline);

/* DISPLAY */
void	display_phrase(t_line *cmd);
void	display_word(t_token *phrase);

/* UTILS */
int		ft_isquote(int c);
int		ft_isredir(int c);
int		ft_isspace(int c);
int		ft_isarg(int c);
int		ft_isenv(int c);
char	*ft_freedup(char *str_free, char *str);

#endif
