/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:12:40 by gromiti           #+#    #+#             */
/*   Updated: 2024/04/21 19:02:47 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_newline(const char	*st_buff)
{
	char	*str;
	size_t	i;

	str = (char *)st_buff;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}

size_t	ft_index_newline(const char *st_buff)
{
	char	*str;
	size_t	i;

	str = (char *)st_buff;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		return (i);
	return (0);
}
