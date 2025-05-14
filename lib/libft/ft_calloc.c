/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:16:35 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/12 12:16:39 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	size_tot;

	size_tot = nmemb * size;
	if (nmemb + size < size || size + nmemb < nmemb || size_tot > 2147483424)
		return (NULL);
	res = malloc(size_tot);
	if (res == NULL)
		return (NULL);
	while (size_tot--)
		((char *)res)[size_tot] = 0;
	return (res);
}
