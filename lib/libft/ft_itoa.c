/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 14:26:57 by gromiti           #+#    #+#             */
/*   Updated: 2024/01/22 17:11:49 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_num_lenght(int n)
{
	size_t	lenght;

	lenght = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		lenght++;
	while (n != 0)
	{
		n /= 10;
		lenght++;
	}
	return (lenght);
}

char	*ft_itoa(int n)
{
	char		*num;
	int			cont;
	long int	nb;

	nb = (long int)n;
	cont = ft_num_lenght(n);
	num = (char *)malloc(sizeof(char) * (ft_num_lenght(n) + 1));
	if (!num)
		return (NULL);
	num[cont] = '\0';
	cont -= 1;
	if (n == 0)
		num[0] = '0';
	if (n < 0)
	{
		num[0] = '-';
		nb *= -1;
	}
	while (nb != 0)
	{
		num[cont] = (nb % 10) + '0';
		nb /= 10;
		cont --;
	}
	return (num);
}
