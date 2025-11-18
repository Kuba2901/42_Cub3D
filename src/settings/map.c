/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:44:41 by gromiti           #+#    #+#             */
/*   Updated: 2025/06/23 18:01:00 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_settings_map.h>
#include <stdlib.h>
#include <utils.h>
#include <stdio.h>
#include <fcntl.h>
#include <libft.h>
#include <cube_settings_textures.h>

static size_t	settings_map_config_count_enemies(
	char **map, int width, int height)
{
	size_t	count;
	int		y;
	int		x;

	if (!map)
		return (0);
	count = 0;
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			if (map[y][x] && map[y][x] == 'X')
				count++;
		}
	}
	return (count);
}

static void	settings_map_process_enemy_position(t_point **enemies_locations,
	char **map, t_point pos, int *i)
{
	if (map[pos.y][pos.x] && map[pos.y][pos.x] == 'X')
	{
		enemies_locations[*i] = map_point_init_heap(
				pos.x, pos.y, map[pos.y][pos.x]);
		(*i)++;
	}
}

t_point	**settings_map_config_get_enemies_locations(
	char **map, int width, int height)
{
	size_t	enemies_count;
	t_point	**enemies_locations;
	t_point	pos;
	int		i;

	enemies_count = settings_map_config_count_enemies(map, width, height);
	if (!enemies_count)
		return (NULL);
	enemies_locations = malloc(sizeof(t_point *) * (enemies_count + 1));
	if (!enemies_locations)
		return (NULL);
	pos.y = -1;
	i = 0;
	while (++pos.y < height)
	{
		pos.x = -1;
		while (++pos.x < width)
			settings_map_process_enemy_position(
				enemies_locations, map, pos, &i);
	}
	enemies_locations[i] = NULL;
	return (enemies_locations);
}

// static t_bool	settings_map_config_is_start(char c)
// {
// 	return (c == 'E' || c == 'W' || c == 'S' || c == 'N');
// }

t_map_config	*settings_map_config_init(char **map, int width, int height)
{
	t_map_config	*map_config;

	map_config = malloc(sizeof(t_map_config));
	if (!map_config)
	{
		printf("Failed to allocate memory for map_config.\n");
		return (NULL);
	}
	map_config->enemies_locations = settings_map_config_get_enemies_locations(
			map, width, height);
	map_config->enemies_count = settings_map_config_count_enemies(
			map, width, height);
	map_config->height = height;
	map_config->width = width;
	map_config->map = map;
	settings_map_config_extract_basic_information(map_config);
	return (map_config);
}
