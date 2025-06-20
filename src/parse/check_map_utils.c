/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gromiti <gromiti@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:33:32 by gromiti           #+#    #+#             */
/*   Updated: 2025/06/20 15:49:09 by gromiti          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse_map_utils.h>
#include <parse_mandatory.h>

void	check_starting_pos_map(t_parser_config *parser_config)
{
	int		i;
	int		j;
	int		start_found;
	char	elem;

	i = -1;
	start_found = 0;
	while (++i < (int)parser_config->map_config->height)
	{
		j = -1;
		while (++j < (int)parser_config->map_config->width)
		{
			elem = parser_config->map_config->map[i][j];
			if (elem == 'N' || elem == 'S' || elem == 'E' || elem == 'W')
				start_found++;
			if (start_found > 1)
				free_parser_config(parser_config, NULL, \
					"Error\nMultiple starting point found.\n");
		}
	}
	if (!start_found)
		free_parser_config(parser_config, NULL, \
			"Error\nNo starting point found.\n");
}

int	is_neighbour(char **map, int i, int j, char elem)
{
	if (map[i - 1][j] == elem || map[i + 1][j] == elem || \
		map[i][j - 1] == elem || map[i][j + 1] == elem)
	{
		return (1);
	}
	return (0);
}

void	check_map_walls(t_parser_config *parser_config)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)parser_config->map_config->height)
	{
		j = -1;
		while (++j < (int)parser_config->map_config->width)
		{
			if (parser_config->map_config->map[i][j] == '0')
			{
				if (i == 0 || i == (int)parser_config->map_config->height - 1 \
					|| j == 0 || j == (int)parser_config->map_config->width - 1)
					free_parser_config(parser_config, NULL, \
						"Error\nMap is not closed.\n");
				if (is_neighbour(parser_config->map_config->map, i, j, ' ') || \
					is_neighbour(parser_config->map_config->map, i, j, '\t'))
					free_parser_config(parser_config, NULL, \
						"Error\nMap is not closed.\n");
			}
		}
	}
}

int	check_exit(t_parser_config *parser_config)
{
	int	i;

	i = -1;
	while (++i < (int)parser_config->map_config->height)
	{
		if (ft_strchr(parser_config->map_config->map[i], 'Q'))
			return (1);
	}
	free_parser_config(parser_config, NULL, \
		"Error\nExit not found in the map.\n");
	return (0);
}
