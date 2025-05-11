/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 21:22:22 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:22:49 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_MAP_H
# define CUBE_MAP_H

# include <utils.h>

typedef struct s_vector
{
	double	dir_x;
	double	dir_y;
}	t_vector;

typedef struct s_point
{
	int		x;
	int		y;
	char	c;
}	t_point;

typedef struct s_map
{
	t_point	**tiles;
	int		height;
	int		width;
}	t_map;

typedef struct s_map		t_map;
typedef struct s_cube		t_cube;
typedef struct s_map_config	t_map_config;

t_point	map_point_init(int x, int y, char c);
t_point	*map_point_init_heap(int x, int y, char c);
t_map	*map_map_init(t_map_config *config);
void	map_map_free(t_map *map);
t_bool	map_is_within_bounds(int x, int y, t_map map);
t_bool	map_is_walkable(t_point pt);
t_bool	map_is_door_open(t_cube *cube);
int		map_dda_is_hit(t_cube *cube, t_point pt);

#endif