/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_floor_ceiling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 19:56:17 by jnenczak         ###   ########.fr       */
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

static void	draw_render_floor(t_cube *cube, t_draw_horizontal_data *dhd, int y)
{
	int		x;
	size_t	**textures;

	textures = cube->cube_settings->tex_config->textures;
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		dhd->cell_x = (int)(dhd->floor_x);
		dhd->cell_y = (int)(dhd->floor_y);
		dhd->texture_x = (int)(TEXTURE_SIZE
				* (dhd->floor_x - dhd->cell_x)) & (TEXTURE_SIZE - 1);
		dhd->texture_y = (int)(TEXTURE_SIZE
				* (dhd->floor_y - dhd->cell_y)) & (TEXTURE_SIZE - 1);
		dhd->floor_x += dhd->floor_step_x;
		dhd->floor_y += dhd->floor_step_y;
		dhd->color = textures[TEX_TYPE_FLOOR]
		[TEXTURE_SIZE * dhd->texture_y + dhd->texture_x];
		dhd->color = (dhd->color >> 1) & 8355711;
		draw_my_mlx_pixel_put(cube->mlx_handler->mlx_img, x, y, dhd->color);
	}
}

static void	draw_render_ceiling(t_cube *cube,
	t_draw_horizontal_data *dhd, int y)
{
	int		x;
	size_t	**textures;

	textures = cube->cube_settings->tex_config->textures;
	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		dhd->cell_x = (int)(dhd->floor_x);
		dhd->cell_y = (int)(dhd->floor_y);
		dhd->texture_x = (int)(TEXTURE_SIZE
				* (dhd->floor_x - dhd->cell_x)) & (TEXTURE_SIZE - 1);
		dhd->texture_y = (int)(TEXTURE_SIZE
				* (dhd->floor_y - dhd->cell_y)) & (TEXTURE_SIZE - 1);
		dhd->floor_x += dhd->floor_step_x;
		dhd->floor_y += dhd->floor_step_y;
		dhd->color = textures[TEX_TYPE_CEILING]
		[TEXTURE_SIZE * dhd->texture_y + dhd->texture_x];
		dhd->color = (dhd->color >> 1) & 8355711;
		draw_my_mlx_pixel_put(cube->mlx_handler->mlx_img,
			x, WINDOW_HEIGHT - y - 1, dhd->color);
	}
}

void	draw_render_floor_and_ceiling(t_cube *cube)
{
	t_draw_horizontal_data	dhd;
	int						y;
	float					floor_x_init;
	float					floor_y_init;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		dhd = draw_prep_get_draw_horizontal_data(cube, y);
		floor_x_init = dhd.floor_x;
		floor_y_init = dhd.floor_y;
		draw_render_floor(cube, &dhd, y);
		dhd.floor_x = floor_x_init;
		dhd.floor_y = floor_y_init;
		draw_render_ceiling(cube, &dhd, y);
	}
}
