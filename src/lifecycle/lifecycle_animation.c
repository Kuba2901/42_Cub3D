/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle_animation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 21:15:00 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/14 19:24:55 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_lifecycle.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>
#include <cube.h>
#include <cube_entities.h>

static void	lifecycle_animate_enemy(t_enemy *enemy)
{
	int						frame;
	t_animation_controller	*controller;

	controller = enemy->base->controller;
	if (controller->playing)
	{
		frame = ++controller->current->frame;
		if (frame >= controller->current->frames_ptr->frames_count - 1
			&& !controller->repeat)
		{
			controller->playing = CUBE_FALSE;
			controller->current = controller->idle;
			controller->current->frame = 0;
		}
		controller->current->frame
			= frame % (controller->current->frames_ptr->frames_count);
	}
}

static void	lifecycle_animate_exit_handle_open(t_cube *cube, int frame)
{
	t_animation_controller	*controller;

	controller = cube->entities->exit->base->controller;
	if (frame >= controller->current->frames_ptr->frames_count
		&& !controller->repeat)
	{
		--controller->current->frame;
	}
	else
	{
		controller->current->frame
			= frame % (controller->current->frames_ptr->frames_count);
	}
}

static void	lifecycle_animate_exit_aux(t_cube *cube)
{
	t_animation_controller	*controller;

	controller = cube->entities->exit->base->controller;
	if (controller->current->frame == 0)
	{
		cube->entities->exit->unlocked = CUBE_FALSE;
		controller->playing = CUBE_FALSE;
	}
	else if (controller->current->frame
		== controller->current->frames_ptr->frames_count - 1)
	{
		cube->entities->exit->unlocked = CUBE_TRUE;
		controller->playing = CUBE_FALSE;
	}
}

static void	lifecycle_animate_exit(t_cube *cube)
{
	int						frame;
	t_animation_controller	*controller;

	controller = cube->entities->exit->base->controller;
	if (controller->playing)
	{
		if (controller->current->frame != 0 && controller->reverse)
			frame = --controller->current->frame;
		else
			frame = ++controller->current->frame;
		lifecycle_animate_exit_handle_open(cube, frame);
		lifecycle_animate_exit_aux(cube);
	}
}

void	lifecycle_animate_sprites(t_cube *cube)
{
	int				i;
	static double	last_time = 0;
	double			current_time;

	current_time = lifecycle_get_ticks();
	if (!cube->entities || !cube->entities->enemies)
		return ;
	if (current_time - last_time >= 250)
	{
		i = -1;
		while (cube->entities->enemies[++i])
			lifecycle_animate_enemy(cube->entities->enemies[i]);
		lifecycle_animate_exit(cube);
		last_time = current_time;
	}
}
