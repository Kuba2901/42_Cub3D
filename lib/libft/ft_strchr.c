/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:44:10 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/11 12:59:55 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	cast;
	int		t;

	cast = (char) c;
	t = 0;
	if (*s == '\0' && c != 0)
		return (0);
	while (*s != '\0')
	{
		if (*s == cast)
		{
			return ((char *)s);
			t = 1;
		}
		s++;
	}
	if (*s == cast)
		return ((char *)s);
	if (t == 1)
		return ((char *)s);
	return (0);
}
