/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_position.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:22:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:37:44 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_settings_map.h>
#include <cube.h>
#include <math.h>
#include <cube_sprites.h>

double	sprite_get_distance(t_enemy *enemy, t_player *player)
{
	return ((player->base->current_location.x - enemy->base->current_location.x)
		* (player->base->current_location.x - enemy->base->current_location.x)
		+ (player->base->current_location.y - enemy->base->current_location.y)
		* (player->base->current_location.y - enemy->base->current_location.y));
}

void	sprite_calculate_position(t_enemy *sprite, t_player *player,
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

void	sprite_calculate_dimensions(t_sprite_data *data)
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
