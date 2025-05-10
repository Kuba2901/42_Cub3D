/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:22:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:29:35 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_settings_map.h>
#include <cube.h>
#include <cube_drawing.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>
#include <math.h>
#include <stdlib.h>

void	sprite_sort(int *order, double *dist, int amount)
{
	int		temp_order;
	double	temp_dist;
	int		i;
	int		j;

	i = -1;
	while (++i < amount)
	{
		j = -1;
		while (++j < amount)
		{
			if (dist[j] < dist[j + 1])
			{
				temp_dist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = temp_dist;
				temp_order = order[j];
				order[j] = order[j + 1];
				order[j + 1] = temp_order;
			}
		}
	}
}

static int	sprite_count_enemies(t_enemy **enemies)
{
	int	count;

	count = 0;
	if (!enemies)
		return (0);
	while (enemies[count] != NULL)
		count++;
	return (count);
}

static double	sprite_get_distance(t_enemy *enemy, t_player *player)
{
	return ((player->base->current_location.x - enemy->base->current_location.x)
		* (player->base->current_location.x - enemy->base->current_location.x)
		+ (player->base->current_location.y - enemy->base->current_location.y)
		* (player->base->current_location.y - enemy->base->current_location.y));
}

static void	sprite_calculate_distances(t_enemy **enemies,
			t_entities *entities, int num_sprites)
{
	int	i;

	i = 0;
	while (i < num_sprites)
	{
		entities->sprite_order[i] = i;
		entities->sprite_distance[i] = sprite_get_distance(
				enemies[i], entities->player);
		i++;
	}
	sprite_sort(entities->sprite_order,
		entities->sprite_distance, num_sprites);
}

static void	sprite_calculate_position(t_enemy *sprite, t_player *player,
			t_sprite_data *data)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = sprite->base->current_location.x
		- player->base->current_location.x;
	sprite_y = sprite->base->current_location.y
		- player->base->current_location.y;
	inv_det = 1.0 / (player->camera.dir_x * player->dir.dir_y
			- player->dir.dir_x * player->camera.dir_y);
	data->transform_x = inv_det * (player->dir.dir_y * sprite_x
			- player->dir.dir_x * sprite_y);
	data->transform_y = inv_det * (-player->camera.dir_y * sprite_x
			+ player->camera.dir_x * sprite_y);
	data->screen_x = (int)((WINDOW_WIDTH / 2)
			* (1 + data->transform_x / data->transform_y));
}

static void	sprite_calculate_dimensions(t_sprite_data *data)
{
	data->height = abs((int)(WINDOW_HEIGHT / data->transform_y));
	data->width = data->height;
	data->draw_start_y = -data->height / 2 + WINDOW_HEIGHT / 2;
	if (data->draw_start_y < 0)
		data->draw_start_y = 0;
	data->draw_end_y = data->height / 2 + WINDOW_HEIGHT / 2;
	if (data->draw_end_y >= WINDOW_HEIGHT)
		data->draw_end_y = WINDOW_HEIGHT - 1;
	data->draw_start_x = -data->width / 2 + data->screen_x;
	if (data->draw_start_x < 0)
		data->draw_start_x = 0;
	data->draw_end_x = data->width / 2 + data->screen_x;
	if (data->draw_end_x >= WINDOW_WIDTH)
		data->draw_end_x = WINDOW_WIDTH - 1;
}

static t_sprite_tex_data	sprite_init_tex_data(t_sprite_data *data,
	t_enemy *sprite, int stripe)
{
	t_sprite_tex_data	tex_data;

	tex_data.tex_x = (int)(256 * (stripe - (-data->width / 2 + data->screen_x))
			* TEXTURE_SIZE / data->width) / 256;
	tex_data.tex = sprite->base->controller->current->frames_ptr->frames
	[sprite->base->controller->current->frame];
	return (tex_data);
}

static void	sprite_draw_stripe(t_cube *cube, t_enemy *sprite,
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

static void	sprite_process(t_cube *cube, t_enemy *sprite,
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

static void	sprite_draw(t_cube *cube, t_enemy *sprite)
{
	t_sprite_data	data;
	t_player		*player;

	player = cube->entities->player;
	sprite_calculate_position(sprite, player, &data);
	sprite_calculate_dimensions(&data);
	sprite_process(cube, sprite, &data);
}

void	sprites_draw(t_cube *cube)
{
	t_entities	*entities;
	t_enemy		**enemies;
	int			num_sprites;
	int			i;

	entities = cube->entities;
	enemies = entities->enemies;
	num_sprites = sprite_count_enemies(enemies);
	if (num_sprites == 0)
		return ;
	sprite_calculate_distances(enemies, entities, num_sprites);
	i = 0;
	while (i < num_sprites)
	{
		sprite_draw(cube, enemies[entities->sprite_order[i]]);
		i++;
	}
}
