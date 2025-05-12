/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:33:14 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/09 15:47:58 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	int		t;

	res = (char *)s;
	t = 0;
	if (*s == '\0' && c != 0)
		return (0);
	while (*s != '\0')
	{
		if (*s == (char)c)
		{
			res = (char *)s;
			t = 1;
		}
		s++;
	}
	if (*s == (char)c)
	{
		res = (char *)s;
		return (res);
	}
	if (t)
		return (res);
	return (0);
}
