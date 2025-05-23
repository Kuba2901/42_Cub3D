/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:00:02 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 21:00:46 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_map.h>
#include <cube.h>
#include <cube_settings.h>
#include <cube_entities.h>
#include <cube_dda.h>
#include <stdlib.h>

t_point	map_point_init(int x, int y, char c)
{
	t_point	pt;

	pt.x = x;
	pt.y = y;
	pt.c = c;
	return (pt);
}

t_point	**map_tiles_init(t_map_config *config)
{
	t_point	**tiles;
	int		y;
	int		x;

	tiles = malloc(sizeof(t_point *) * config->height);
	if (!tiles)
		return (NULL);
	y = -1;
	while (++y < config->height)
	{
		x = -1;
		tiles[y] = malloc(sizeof(t_point) * config->width);
		while (++x < config->width)
			tiles[y][x] = map_point_init(x, y, config->map[y][x]);
	}
	return (tiles);
}

void	map_tiles_free(t_map *map)
{
	int	y;

	y = -1;
	while (++y < map->height)
		safe_free(map->tiles[y]);
	safe_free(map->tiles);
}

t_map	*map_map_init(t_map_config *config)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = config->height;
	map->width = config->width;
	map->tiles = map_tiles_init(config);
	return (map);
}

void	map_map_free(t_map *map)
{
	if (!map)
		return ;
	map_tiles_free(map);
	free(map);
	map = NULL;
}
