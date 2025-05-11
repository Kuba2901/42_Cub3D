/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 19:53:13 by jnenczak         ###   ########.fr       */
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

void	draw_render_clear_screen(t_cube *cube)
{
	if (cube->mlx_handler->mlx_img->img != NULL)
		mlx_destroy_image(cube->mlx_handler->mlx,
			cube->mlx_handler->mlx_img->img);
	cube->mlx_handler->mlx_img->img = mlx_new_image(
			cube->mlx_handler->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	cube->mlx_handler->mlx_img->addr = mlx_get_data_addr(
			cube->mlx_handler->mlx_img->img,
			&cube->mlx_handler->mlx_img->bits_per_pixel,
			&cube->mlx_handler->mlx_img->line_length,
			&cube->mlx_handler->mlx_img->endian);
}

void	draw_render_calculate_and_draw_single_stripe(int x, t_cube *cube)
{
	t_dda_data	*dda;
	double		camera_x;

	dda = cube->dda_data;
	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	dda_setup(cube, camera_x);
	dda_set_step_and_initial_side_dist(cube);
	dda_perform(cube);
	if (dda->hit_type == HORIZONTAL)
		dda->perp_wall_dist = (dda->side_dist_x - dda->delta_dist_x);
	else
		dda->perp_wall_dist = (dda->side_dist_y - dda->delta_dist_y);
	dda->wall_height = (int)(WINDOW_HEIGHT / dda->perp_wall_dist);
	cube->entities->buffer_z[x] = dda->perp_wall_dist;
	draw_textured_vertical_slice(x, cube);
}

void	draw_render_scene(t_cube *cube)
{
	int	x;

	if (!cube || !cube->entities || !cube->entities->player
		|| !cube->dda_data || !cube->mlx_handler
		|| !cube->mlx_handler->mlx_img)
	{
		printf("Error: NULL pointers detected in draw_scene\n");
		return ;
	}
	draw_prep_dda(cube);
	draw_render_clear_screen(cube);
	draw_render_floor_and_ceiling(cube);
	x = -1;
	while (++x < WINDOW_WIDTH)
		draw_render_calculate_and_draw_single_stripe(x, cube);
	sprites_draw(cube);
	draw_minimap(cube);
	mlx_put_image_to_window(cube->mlx_handler->mlx,
		cube->mlx_handler->mlx_win,
		cube->mlx_handler->mlx_img->img, 0, 0);
}
