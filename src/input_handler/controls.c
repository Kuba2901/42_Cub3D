/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:38:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:17:41 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_input_handler.h>
#include <cube_map.h>
#include <cube.h>
#include <cube_entities.h>
#include <cube_runtime.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>
#include <math.h>
#include <stdio.h>
#include <cube_controls.h>

t_bool	is_walkable(t_cube *cube, t_point pt)
{
	if (pt.x == (int)cube->entities->exit->base->current_location.x
		&& pt.y == (int)cube->entities->exit->base->current_location.y
		&& cube->entities->exit->unlocked)
		return (CUBE_TRUE);
	return (map_is_walkable(pt));
}

void	input_handler_action(t_cube *cube)
{
	t_input_handler_keys	*keys;
	t_exit					*exit;
	int						frame;
	t_animation				*current;

	keys = cube->input_handler->keys;
	exit = cube->entities->exit;
	current = exit->base->controller->current;
	frame = current->frame;
	if (keys->e)
	{
		if (current->type == ANIM_TYPE_OPEN
			&& frame == current->frames_ptr->frames_count - 1)
			anim_animation_controller_player_start(
				exit->base->controller, ANIM_TYPE_OPEN, CUBE_TRUE);
		else
			anim_animation_controller_player_start(
				exit->base->controller, ANIM_TYPE_OPEN, CUBE_FALSE);
	}
}

void	mov_handler(t_cube *cube)
{
	double					m_speed;
	double					r_speed;
	t_runtime_handler		*rh;
	t_input_handler_keys	*keys;

	rh = cube->runtime_handler;
	keys = cube->input_handler->keys;
	rh->frametime = (rh->time - rh->old_time) / 1000.0;
	m_speed = rh->frametime * 5.0;
	r_speed = rh->frametime * 3.0;
	if (keys->w || keys->s)
		handle_for_back(cube, m_speed);
	if (keys->a || keys->d)
		handle_left_right(cube, m_speed);
	if (keys->left || keys->right)
		handle_rotation(cube, r_speed);
	if (keys->escape)
		cube->runtime_handler->running = CUBE_FALSE;
	if (keys->e)
		input_handler_action(cube);
}
