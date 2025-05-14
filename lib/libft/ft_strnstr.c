/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:08:05 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/11 13:33:25 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	int		cont2;

	if (*s2 == '\0')
		return ((char *)s1);
	if (len == 0)
		return (NULL);
	while (*s1 && len)
	{
		cont2 = 0;
		while ((*(s1 + cont2) == s2[cont2]) && (len - cont2) > 0)
		{
			if (s2[cont2 + 1] == '\0' && s2[0] != '\0')
				return ((char *)s1);
			cont2++;
		}
		s1++;
		len--;
	}
	return (NULL);
}
