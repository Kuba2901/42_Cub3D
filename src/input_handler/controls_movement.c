/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:38:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:52:11 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_input_handler.h>
#include <cube_map.h>
#include <cube.h>
#include <cube_entities.h>
#include <cube_runtime.h>
#include <math.h>
#include <cube_controls.h>

static void	move_player(t_cube *cube, double new_x, double new_y)
{
	t_player	*player;
	t_point		pt;

	player = cube->entities->player;
	pt = cube->map->tiles[(int)new_y][(int)new_x];
	if (is_walkable(cube, pt))
	{
		player->base->current_location.x = new_x;
		player->base->current_location.y = new_y;
	}
}

void	handle_left_right(t_cube *cube, double move_speed)
{
	double					new_x;
	double					new_y;
	t_player				*player;
	t_input_handler_keys	*keys;
	t_vector				side_dir;

	player = cube->entities->player;
	keys = cube->input_handler->keys;
	side_dir.dir_x = -player->dir.dir_y;
	side_dir.dir_y = player->dir.dir_x;
	if (keys->a)
	{
		new_x = player->base->current_location.x + side_dir.dir_x * move_speed;
		new_y = player->base->current_location.y + side_dir.dir_y * move_speed;
		move_player(cube, new_x, new_y);
	}
	else if (keys->d)
	{
		new_x = player->base->current_location.x - side_dir.dir_x * move_speed;
		new_y = player->base->current_location.y - side_dir.dir_y * move_speed;
		move_player(cube, new_x, new_y);
	}
}

void	handle_for_back(t_cube *cube, double move_speed)
{
	double					new_x;
	double					new_y;
	t_player				*player;
	t_input_handler_keys	*keys;

	keys = cube->input_handler->keys;
	player = cube->entities->player;
	if (keys->w)
	{
		new_x = player->base->current_location.x
			+ player->dir.dir_x * move_speed;
		new_y = player->base->current_location.y
			+ player->dir.dir_y * move_speed;
		move_player(cube, new_x, new_y);
	}
	else if (keys->s)
	{
		new_x = player->base->current_location.x
			- player->dir.dir_x * move_speed;
		new_y = player->base->current_location.y
			- player->dir.dir_y * move_speed;
		move_player(cube, new_x, new_y);
	}
}
