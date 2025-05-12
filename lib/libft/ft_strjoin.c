/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:23:20 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/22 15:57:07 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*jp;
	size_t	cont;

	if (!s1 || !s2)
		return (NULL);
	jp = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!jp)
		return (NULL);
	cont = 0;
	while (*s1)
	{
		jp[cont] = *s1;
		cont++;
		s1++;
	}
	while (*s2)
	{
		jp[cont] = *s2;
		cont++;
		s2++;
	}
	jp[cont] = '\0';
	return (jp);
}
