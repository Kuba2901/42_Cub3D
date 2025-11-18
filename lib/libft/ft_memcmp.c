/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:17:09 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/12 12:17:10 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char	*src1;
	char	*src2;

	src1 = (char *)s1;
	src2 = (char *)s2;
	while (n)
	{
		if (*src1 < *src2)
			return ((unsigned char)*src1 - (unsigned char)*src2);
		if (*src1 > *src2)
			return ((unsigned char)*src1 - (unsigned char)*src2);
		src1++;
		src2++;
		n--;
	}
	return (0);
}
