/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:17:23 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/12 12:17:25 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*cp;
	size_t	cont;

	cp = (char *)malloc(ft_strlen(s) + 1);
	if (!cp)
		return (NULL);
	cont = 0;
	while (cont < ft_strlen(s))
	{
		cp[cont] = s[cont];
		cont++;
	}
	cp[cont] = '\0';
	return (cp);
}
