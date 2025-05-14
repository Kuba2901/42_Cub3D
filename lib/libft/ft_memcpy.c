/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 14:59:25 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/11 15:42:33 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n)
	{
		*d = *s;
		d++;
		s++;
		n--;
	}
	return (dest);
}
