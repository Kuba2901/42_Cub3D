/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:51:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 17:03:08 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_dda.h>
#include <cube_mlx_handler.h>
#include <cube.h>
#include <cube_entities.h>
#include <stdlib.h>
#include <cube_map.h>
#include <math.h>

void	dda_setup(t_cube *cube, double camera_x)
{
	t_player	*player;
	t_dda_data	*dda;

	player = cube->entities->player;
	dda = cube->dda_data;
	dda->dir_vect = player->dir;
	dda->camera_dir = player->camera;
	dda->ray_dir.dir_x = dda->dir_vect.dir_x + dda->camera_dir.dir_x * camera_x;
	dda->ray_dir.dir_y = dda->dir_vect.dir_y + dda->camera_dir.dir_y * camera_x;
	dda->pos_x = player->base->current_location.x;
	dda->pos_y = player->base->current_location.y;
	dda->map_x = (int)dda->pos_x;
	dda->map_y = (int)dda->pos_y;
	if (dda->ray_dir.dir_x == 0)
		dda->delta_dist_x = 1e30;
	else
		dda->delta_dist_x = fabs(1 / dda->ray_dir.dir_x);
	if (dda->ray_dir.dir_y == 0)
		dda->delta_dist_y = 1e30;
	else
		dda->delta_dist_y = fabs(1 / dda->ray_dir.dir_y);
}

void	dda_perform(t_cube *cube)
{
	t_dda_data	*dda;
	int			hit;
	t_point		pt;

	hit = 0;
	dda = cube->dda_data;
	while (hit == 0)
	{
		if (dda->side_dist_x < dda->side_dist_y)
		{
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_x += dda->step_x;
			dda->hit_type = HORIZONTAL;
		}
		else
		{
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_y += dda->step_y;
			dda->hit_type = VERTICAL;
		}
		pt.x = dda->map_x;
		pt.y = dda->map_y;
		hit = map_dda_is_hit(cube, pt);
	}
}

void	dda_set_step_and_initial_side_dist(t_cube *cube)
{
	t_dda_data	*dda;

	dda = cube->dda_data;
	if (dda->ray_dir.dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (dda->pos_x - dda->map_x) * dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_x + 1.0 - dda->pos_x) * dda->delta_dist_x;
	}
	if (dda->ray_dir.dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (dda->pos_y - dda->map_y) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_y + 1.0 - dda->pos_y) * dda->delta_dist_y;
	}
}

t_dda_data	*dda_init( void )
{
	t_dda_data	*dda_data;

	dda_data = malloc(sizeof(t_dda_data));
	if (!dda_data)
		return (NULL);
	return (dda_data);
}

void	dda_free(t_dda_data *dda)
{
	safe_free(dda);
}
