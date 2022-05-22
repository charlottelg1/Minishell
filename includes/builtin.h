/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:04:07 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/04 21:29:02 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

int		is_builtin(char **args);
int		exec_builtin(char **args, t_line cmd);

/* UTILS */
char	*join_args(char **av);
int		size_list(t_env	*l_env);
void	lst_cpy(t_env *new, t_env *old, int i);

/* ECHO */
int		echo_cmd(char **args, t_line cmd, t_bifunct *bifunct);

/* PWD */
int		pwd_cmd(char **args, t_line cmd, t_bifunct *bifunct);

/* CD */
int		cd_cmd(char **args, t_line cmd, t_bifunct *bifunct);
void	change_env_cd(t_env	*l_env);
char	*ft_freejoinfirst(char *str1, char *str2);

/* UNSET */
int		unset_cmd(char **args, t_line cmd, t_bifunct *bifunct);

/* EXPORT */
int		export_cmd(char **args, t_line cmd, t_bifunct *bifunct);
char	**ft_split(char const *s, char c);
char	**export_no_args(char **env);
void	l_env_new_node(t_env *l_env, char *str);
int		ft_strcmp(char *s1, char *s2);
int		check_args(char **tab);
int		ret_expnoargs(char **env);
int		var_exist(char *var);
int		valid_arg(char *str, t_line cmd);
int		caract_ok_export(char c);
char	**lst_to_tab(t_env	*l_env);
char	**sort_tab(char **env_sort, int len);
char	*get_quotes(char *str);
void	msg_valid_id(char *str, t_line cmd);
void	free_tablines(char **tab);

/* EXIT */
int		exit_cmd(char **args, t_line cmd, t_bifunct *bifunct);

/* ENV */
int		env_cmd(char **args, t_line cmd, t_bifunct *bifunct);
t_env	*env_to_list(char **env);
t_env	*ft_listdup(t_env *l_env);
void	lst_gofront(t_env *lst);
void	lst_goback(t_env *lst);
int		hasequal(char *str);
char	**get_smallenv(char **env);

/* DISPLAY a SUPP */
void	display_tab(char **tab);
void	display_lst(t_env *env);

#endif
