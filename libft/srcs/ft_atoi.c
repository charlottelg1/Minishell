/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 22:15:17 by root              #+#    #+#             */
/*   Updated: 2021/05/20 14:40:16 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkoverflow(const char *nptr, int sign)
{
	int	i;

	i = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		i++;
		nptr++;
	}
	if (i >= 19)
	{
		if (sign == 1)
			return (-1);
		if (sign == -1)
			return (0);
	}
	return (2);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (checkoverflow(nptr, sign) < 2)
		return (checkoverflow(nptr, sign));
	while (*nptr >= '0' && *nptr <= '9')
	{
		result = result * 10 + *nptr - 48;
		nptr++;
	}
	return (result * sign);
}
