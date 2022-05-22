/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 17:41:25 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 17:43:06 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef enum type
{
	NONE,
	ARG,
	ARG_SQ,
	ARG_DQ,
	FILE_IN,
	FILE_OUT,
	HERE_DOC,
	FILE_OUT_SUR,
	OPEN_FILE,
	EXIT_FILE,
	LIMITOR,
	EXIT_FILE_RET,
	WRONG_REDIR,
	IS_SPACE
}	t_type;

typedef struct s_env
{
	char			*str;
	struct s_env	*previous;
	struct s_env	*next;
	int				size;
	int				type;
}	t_env;

typedef struct s_token
{
	char			*word;
	t_type			type;
	int				fdout;
	int				fdin;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_line
{
	char			*prompt;
	char			*phrase;
	int				word_num;
	t_token			*word;
	char			**args;
	char			**env;
	t_env			*l_env;
	struct s_line	*next;
	int				ret;
	int				redir[2];
	int				savestd[2];
}	t_line;

typedef struct s_bifunct
{
	char	*cmd;
	int		(*pf)(char **, t_line, struct s_bifunct *);
}	t_bifunct;

typedef struct s_global
{
	int		ret;
	t_line	*cmdline;
}	t_global;

#endif
