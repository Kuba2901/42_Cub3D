/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_prep_and_calc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 22:03:17 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_mlx_handler.h>
#include <cube_dda.h>
#include <cube_entities.h>
#include <cube_drawing.h>
#include <cube_settings.h>
#include <mlx.h>
#include <math.h>
#include <stdio.h>
#include <cube_minimap.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>

static double	draw_prep_get_wall_x(t_cube *cube)
{
	t_dda_data	*dda;
	t_player	*player;
	double		wall_x;

	dda = cube->dda_data;
	player = cube->entities->player;
	if (dda->hit_type == HORIZONTAL)
		wall_x = player->base->current_location.y
			+ dda->perp_wall_dist * dda->ray_dir.dir_y;
	else
		wall_x = player->base->current_location.x
			+ dda->perp_wall_dist * dda->ray_dir.dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}

static t_tex_type	draw_prep_determine_face_hit(t_dda_data *dda)
{
	if (dda->hit_type == HORIZONTAL)
	{
		if (dda->step_x > 0)
			return (TEX_TYPE_WEST);
		else
			return (TEX_TYPE_EAST);
	}
	else
	{
		if (dda->step_y > 0)
			return (TEX_TYPE_NORTH);
		else
			return (TEX_TYPE_SOUTH);
	}
}

t_draw_vertical_slice_data	draw_prep_vertical_slice_data(
	t_cube *cube, int column_x)
{
	t_draw_vertical_slice_data	data;
	t_dda_data					*dda;

	dda = cube->dda_data;
	data.tex_type = 0;
	if (cube->map->tiles[dda->map_y][dda->map_x].c >= '1'
		&& cube->map->tiles[dda->map_y][dda->map_x].c
		<= '0' + TEXTURE_TYPES_COUNT)
		data.tex_type = (int)draw_prep_determine_face_hit(dda);
	data.tex_x = (int)(draw_prep_get_wall_x(cube) * (double)TEXTURE_SIZE);
	if (dda->hit_type == HORIZONTAL && dda->ray_dir.dir_x < 0)  // Changed > to 
		data.tex_x = TEXTURE_SIZE - data.tex_x - 1;
	if (dda->hit_type == VERTICAL && dda->ray_dir.dir_y > 0)    // Changed < to >
		data.tex_x = TEXTURE_SIZE - data.tex_x - 1;
	data.wall_top = ((WINDOW_HEIGHT / 2.0) - (dda->wall_height / 2.0));
	data.wall_bottom = ((WINDOW_HEIGHT / 2.0) + (dda->wall_height / 2.0));
	data.step = 1.0 * TEXTURE_SIZE / dda->wall_height;
	if (data.wall_top < 0)
		data.tex_pos = -data.wall_top * data.step;
	else
		data.tex_pos = 0;
	data.column_x = column_x;
	if (cube->map->tiles[dda->map_y][dda->map_x].c == 'Q')
		data.tex_type = TEX_TYPE_EXIT;
	return (data);
}

t_draw_horizontal_data	draw_prep_get_draw_horizontal_data(
	t_cube *cube, int y)
{
	t_dda_data				*dda;
	t_draw_horizontal_data	dhd;

	dda = cube->dda_data;
	dhd.ray_dir_x0 = dda->dir_vect.dir_x - dda->camera_dir.dir_x;
	dhd.ray_dir_y0 = dda->dir_vect.dir_y - dda->camera_dir.dir_y;
	dhd.ray_dir_x1 = dda->dir_vect.dir_x + dda->camera_dir.dir_x;
	dhd.ray_dir_y1 = dda->dir_vect.dir_y + dda->camera_dir.dir_y;
	dhd.pos_rel_to_horizon = y - WINDOW_HEIGHT / 2;
	dhd.pos_vertical_z = 0.5 * WINDOW_HEIGHT;
	dhd.row_distance = dhd.pos_vertical_z / dhd.pos_rel_to_horizon;
	dhd.floor_step_x = dhd.row_distance
		* (dhd.ray_dir_x1 - dhd.ray_dir_x0) / WINDOW_WIDTH;
	dhd.floor_step_y = dhd.row_distance
		* (dhd.ray_dir_y1 - dhd.ray_dir_y0) / WINDOW_WIDTH;
	dhd.floor_x = dda->pos_x + dhd.row_distance * dhd.ray_dir_x0;
	dhd.floor_y = dda->pos_y + dhd.row_distance * dhd.ray_dir_y0;
	return (dhd);
}

void	draw_prep_dda(t_cube *cube)
{
	t_player	*player;
	t_dda_data	*dda;

	player = cube->entities->player;
	dda = cube->dda_data;
	dda->pos_x = player->base->current_location.x;
	dda->pos_y = player->base->current_location.y;
	dda->dir_vect = player->dir;
	dda->camera_dir = player->camera;
}
