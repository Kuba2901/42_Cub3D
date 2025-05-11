/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:00:29 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:16:25 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_map.h>
#include <cube.h>
#include <cube_settings.h>
#include <cube_entities.h>
#include <cube_dda.h>
#include <stdlib.h>

int	map_dda_is_hit(t_cube *cube, t_point pt)
{
	t_dda_data	*dda;

	dda = cube->dda_data;
	return (!map_is_within_bounds(pt.x, pt.y, *cube->map)
		|| cube->map->tiles[dda->map_y][dda->map_x].c == '1'
		|| cube->map->tiles[dda->map_y][dda->map_x].c == 'Q');
}

t_bool	map_is_within_bounds(int x, int y, t_map map)
{
	if (y < 0 || y >= map.height)
		return (CUBE_FALSE);
	if (x < 0 || x >= map.width)
		return (CUBE_FALSE);
	if (map.tiles[y][x].c == 'O')
		return (CUBE_FALSE);
	return (CUBE_TRUE);
}

t_bool	map_is_door_open(t_cube *cube)
{
	return (cube->entities->exit->unlocked);
}

t_bool	map_is_walkable(t_point pt)
{
	return (pt.c != '1' && pt.c != 'O' && pt.c != 'Q');
}

t_point	*map_point_init_heap(int x, int y, char c)
{
	t_point	*heap_pt;

	heap_pt = malloc(sizeof(t_point));
	if (!heap_pt)
		return (NULL);
	heap_pt->x = x;
	heap_pt->y = y;
	heap_pt->c = c;
	return (heap_pt);
}
