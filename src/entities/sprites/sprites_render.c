/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:22:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:37:51 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_settings_map.h>
#include <cube.h>
#include <cube_drawing.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>
#include <cube_sprites.h>

t_sprite_tex_data	sprite_init_tex_data(t_sprite_data *data,
	t_enemy *sprite, int stripe)
{
	t_sprite_tex_data	tex_data;

	tex_data.tex_x = (int)(256 * (stripe - (-data->width / 2 + data->screen_x))
			* TEXTURE_SIZE / data->width) / 256;
	tex_data.tex = sprite->base->controller->current->frames_ptr->frames
	[sprite->base->controller->current->frame];
	return (tex_data);
}

void	sprite_draw_stripe(t_cube *cube, t_enemy *sprite,
			t_sprite_data *data, int stripe)
{
	int					y;
	int					d;
	t_sprite_tex_data	tex_data;

	tex_data = sprite_init_tex_data(data, sprite, stripe);
	y = data->draw_start_y;
	while (y < data->draw_end_y)
	{
		d = (y * 256) - (WINDOW_HEIGHT * 128) + (data->height * 128);
		tex_data.tex_y = ((d * TEXTURE_SIZE) / data->height) / 256;
		tex_data.color = 0;
		if (tex_data.tex)
			tex_data.color = tex_data.tex[TEXTURE_SIZE
				* tex_data.tex_y + tex_data.tex_x];
		if ((tex_data.color & 0x00FFFFFF) != 0)
			draw_my_mlx_pixel_put(cube->mlx_handler->mlx_img,
				stripe, y, tex_data.color);
		y++;
	}
}

void	sprite_process(t_cube *cube, t_enemy *sprite,
			t_sprite_data *data)
{
	int	stripe;

	stripe = data->draw_start_x;
	while (stripe < data->draw_end_x)
	{
		if (data->transform_y <= 0 || stripe < 0 || stripe >= WINDOW_WIDTH
			|| data->transform_y >= cube->entities->buffer_z[stripe])
		{
			stripe++;
			continue ;
		}
		sprite_draw_stripe(cube, sprite, data, stripe);
		stripe++;
	}
}
