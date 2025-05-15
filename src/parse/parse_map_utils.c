/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:34:32 by gromiti           #+#    #+#             */
/*   Updated: 2025/05/15 16:43:43 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_map_utils.h>

int	get_new_line_lenght(char *line)
{
	int	i;
	int	spaces;

	i = -1;
	spaces = 0;
	while (line[++i])
	{
		if (line[i] == '\t')
			spaces += TAB_WIDTH - 1;
	}
	if (line[i - 1] != '\n')
		i++;
	return (i + spaces);
}

void	put_spaces(char *new_line, int *j)
{
	int	i;

	i = -1;
	while (++i < TAB_WIDTH)
		new_line[++(*j)] = ' ';
}

char	*replace_tabs(char *line)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = (char *)malloc(sizeof(char) * (get_new_line_lenght(line)));
	if (!new_line)
		return (NULL);
	i = -1;
	j = -1;
	while (line[++i])
	{
		if (line[i] == '\t')
			put_spaces(new_line, &j);
		else if (line[i] == '\n')
		{
			new_line[++j] = '\0';
			return (new_line);
		}
		else
			new_line[++j] = line[i];
	}
	new_line[++j] = '\0';
	return (new_line);
}
