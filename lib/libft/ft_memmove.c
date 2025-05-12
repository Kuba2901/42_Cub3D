/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:10:04 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/11 17:11:08 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		cont;

	d = (char *)dest;
	s = (char *)src;
	cont = 0;
	if (!dest && !src)
		return (NULL);
	if (src < dest && src + n > dest)
	{
		while (n--)
			d[n] = s[n];
		return (dest);
	}
	while (cont < n)
	{
		d[cont] = s[cont];
		cont++;
	}
	return (dest);
}
