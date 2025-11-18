/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:53:20 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/09 17:01:36 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	cont;

	cont = 0;
	while ((*s1 || *s2) && cont < n)
	{
		if ((unsigned char)*s1 < (unsigned char)*s2)
			return (-1);
		if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		s1++;
		s2++;
		cont++;
	}
	return (0);
}
