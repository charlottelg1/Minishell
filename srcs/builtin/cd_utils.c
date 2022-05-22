/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 19:11:34 by cle-gran          #+#    #+#             */
/*   Updated: 2022/05/07 20:26:00 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_newpwd(void)
{
	char	current[4096];
	char	*new_pwd;

	getcwd(current, sizeof(current));
	new_pwd = ft_strjoin("PWD=", current);
	return (new_pwd);
}

char	*get_oldpwd(void)
{
	char	*tmp;
	char	*old_pwd;

	tmp = find_varenv("PWD", g_global.cmdline->env);
	old_pwd = ft_strjoin("OLDPWD=", tmp);
	free(tmp);
	return (old_pwd);
}

void	add_env_cd(char *old_pwd, char *new_pwd, t_env *l_env)
{
	t_env	*tmpenv;
	int		old;

	tmpenv = l_env;
	old = 0;
	while (tmpenv)
	{
		if (ft_strncmp("PWD=", tmpenv->str, 4) == 0)
		{
			free(tmpenv->str);
			tmpenv->str = ft_strdup(new_pwd);
		}
		if (ft_strncmp("OLDPWD=", tmpenv->str, 6) == 0)
		{
			free(tmpenv->str);
			tmpenv->str = ft_strdup(old_pwd);
			old = 1;
		}
		tmpenv = tmpenv->next;
	}
	if (!old)
		l_env_new_node(l_env, old_pwd);
}

void	change_env_cd(t_env	*l_env)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = NULL;
	new_pwd = NULL;
	new_pwd = get_newpwd();
	old_pwd = get_oldpwd();
	add_env_cd(old_pwd, new_pwd, l_env);
	free(new_pwd);
	free(old_pwd);
}
