/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:15:00 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/12 12:13:43 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_lifecycle.h>
#include <cube_runtime.h>
#include <cube_drawing.h>
#include <cube_input_handler.h>
#include <cube.h>
#include <cube_entities.h>
#include <sys/time.h>
#include <stdlib.h>
#include <mlx.h>
#include <cube_audio_integration.h>

int	lifecycle_on_destroy(t_cube *cube)
{
	input_handler_key_press(KEY_ESC, cube);
	return (0);
}

double	lifecycle_get_ticks(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0));
}

static int	lifecycle_check_exit_condition(t_cube *cube)
{
	t_location	exit_loc;
	t_location	player_loc;

	player_loc = cube->entities->player->base->current_location;
	exit_loc = cube->entities->exit->base->current_location;
	if ((int)player_loc.x == (int)exit_loc.x
		&& (int)player_loc.y == (int)exit_loc.y)
	{
		cube->runtime_handler->display_credits = CUBE_TRUE;
		cube_cube_free(cube);
		return (1);
	}
	if (!cube->runtime_handler->running)
	{
		cube_cube_free(cube);
		return (1);
	}
	return (0);
}

int	lifecycle_game_loop(t_cube *cube)
{
	if (lifecycle_check_exit_condition(cube))
		return (0);
	cube->runtime_handler->old_time = cube->runtime_handler->time;
	cube->runtime_handler->time = lifecycle_get_ticks();
	if (cube->runtime_handler->displaying_intro)
	{
		if (cube->mlx_handler->mlx_img->img == NULL)
			intro_display(cube);
		return (0);
	}
	lifecycle_animate_sprites(cube);
	audio_integration_update(cube);
	draw_render_scene(cube);
	mov_handler(cube);
	return (0);
}
