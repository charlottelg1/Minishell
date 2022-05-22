/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 21:48:52 by root              #+#    #+#             */
/*   Updated: 2021/05/23 17:11:01 by cle-gran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned char	c1;

	str = (char *)s;
	c1 = (unsigned char)c;
	while (*str != c1)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return ((char *)str);
}
