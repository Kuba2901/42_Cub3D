/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:08:25 by gromiti           #+#    #+#             */
/*   Updated: 2024/04/25 12:42:30 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_alloc(char **arr, char const *s, char c)
{
	char		**tmp_arr;
	char const	*tmp;

	tmp = s;
	tmp_arr = arr;
	while (*tmp)
	{
		while (*s == c)
			++s;
		tmp = s;
		while (*tmp && *tmp != c)
			++tmp;
		if (*tmp == c || tmp > s)
		{
			*tmp_arr = ft_substr(s, 0, tmp - s);
			s = tmp;
			++tmp_arr;
		}
	}
	*tmp_arr = '\0';
}

static int	ft_count_words(char const *s, char c)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		while (*s == c)
			++s;
		if (*s)
			++count;
		while (*s && *s != c)
			++s;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!arr)
		return (NULL);
	ft_alloc(arr, s, c);
	return (arr);
}
