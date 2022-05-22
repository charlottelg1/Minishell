/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_pipex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cle-gran <cle-gran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 18:07:12 by cle-gran          #+#    #+#             */
/*   Updated: 2022/04/27 18:00:21 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_args(char **args, int nb)
{
	int	i;

	i = 0;
	printf("nb args : %d\n", nb);
	while (i < nb)
	{
		printf("args %d : %s\n", i, args[i]);
		i++;
	}
}
