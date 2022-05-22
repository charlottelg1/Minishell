/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:53:17 by charlottelg       #+#    #+#             */
/*   Updated: 2022/05/07 19:46:12 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "minishell.h"

char	*expanser(char *str, char **env);
char	*ft_expand(char *str, char **env);
char	*ft_freejoin(char *str1, char *str2);
int		get_endalnu(char *str, int i, int *j);
char	*ft_addexp(char *str, int i, int j, char *fstr);
char	*find_varenv(char *str, char **env);
char	*get_varenv(char *str, int *i, int *j, char **env);
char	*find_varenv(char *str, char **env);
int		index_doll(char *str, int i);
int		digit_at(char *str, int i);
char	*expand_ret(char *str);
int		ft_isexpandret(char *str);
char	**lenv_to_env(t_env	*l_env);

#endif
