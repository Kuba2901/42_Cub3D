/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 17:08:17 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 18:39:53 by jnenczak         ###   ########.fr       */
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

static void	draw_textured_regular(t_cube *cube,
	t_draw_vertical_slice_data *data, int y, int tex_y)
{
	unsigned int		color;
	size_t				**textures;

	textures = cube->cube_settings->tex_config->textures;
	color = textures[data->tex_type][TEXTURE_SIZE * tex_y + data->tex_x];
	if (cube->dda_data->hit_type == HORIZONTAL)
		color = (color >> 1) & 8355711;
	draw_my_mlx_pixel_put(cube->mlx_handler->mlx_img,
		data->column_x, y, color);
}

static void	draw_textured_exit(t_cube *cube, t_draw_vertical_slice_data *data,
	int y, int tex_y)
{
	t_animation			*anim;
	unsigned int		color;

	anim = cube->entities->exit->base->controller->current;
	color = anim->frames_ptr->frames[anim->frame]
	[TEXTURE_SIZE * tex_y + data->tex_x];
	if (cube->dda_data->hit_type == HORIZONTAL)
		color = (color >> 1) & 8355711;
	draw_my_mlx_pixel_put(cube->mlx_handler->mlx_img,
		data->column_x, y, color);
}

static t_bool	draw_is_wall(t_cube *cube, t_draw_vertical_slice_data *data,
	int tex_y)
{
	size_t				**textures;

	textures = cube->cube_settings->tex_config->textures;
	return (textures && data->tex_type >= 0
		&& data->tex_type < TEXTURE_TYPES_COUNT
		&& textures[data->tex_type] && tex_y >= 0
		&& tex_y < TEXTURE_SIZE && data->tex_x >= 0
		&& data->tex_x < TEXTURE_SIZE);
}

void	draw_textured(t_draw_vertical_slice_data *data, t_cube *cube, int y)
{
	int					tex_y;

	tex_y = (int)data->tex_pos & (TEXTURE_SIZE - 1);
	data->tex_pos += data->step;
	if (data->tex_type == TEX_TYPE_EXIT)
		draw_textured_exit(cube, data, y, tex_y);
	else if (draw_is_wall(cube, data, tex_y))
		draw_textured_regular(cube, data, y, tex_y);
}
