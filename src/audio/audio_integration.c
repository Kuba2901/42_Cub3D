/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_integration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:55:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:10:14 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_audio.h>
#include <cube_entities.h>
#include <cube_input_handler.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>

static t_bool	audio_is_player_moving(t_cube *cube)
{
	return (cube->input_handler->keys->w
		|| cube->input_handler->keys->a
		|| cube->input_handler->keys->s
		|| cube->input_handler->keys->d);
}

void	audio_update_player_movement(t_cube *cube)
{
	if (!cube->audio_system
		|| !cube->audio_system->sound_loaded[SOUND_FOOTSTEPS])
	{
		return ;
	}
	if (audio_is_player_moving(cube))
	{
		if (!audio_is_sound_playing(cube->audio_system, SOUND_FOOTSTEPS))
			audio_play_sound(cube->audio_system, SOUND_FOOTSTEPS,
				AUDIO_SFX_VOL);
	}
	else
	{
		if (audio_is_sound_playing(cube->audio_system, SOUND_FOOTSTEPS))
			audio_stop_sound(cube->audio_system, SOUND_FOOTSTEPS);
	}
}

void	audio_handle_collectible(t_cube *cube)
{
	if (!cube->audio_system
		|| !cube->audio_system->sound_loaded[SOUND_COLLECTIBLE])
		return ;
	audio_play_sound(cube->audio_system, SOUND_COLLECTIBLE, AUDIO_SFX_VOL);
}

void	audio_handle_elevator(t_cube *cube, t_bool is_opening)
{
	if (!cube->audio_system)
		return ;
	if (!is_opening)
	{
		audio_stop_sound(cube->audio_system, SOUND_ELEVATOR_OPEN);
		return ;
	}
	if (cube->audio_system->sound_loaded[SOUND_ELEVATOR_OPEN])
		audio_play_sound(cube->audio_system, SOUND_ELEVATOR_OPEN,
			AUDIO_SFX_VOL);
}

t_bool	audio_elevator_in_motion(t_cube *cube)
{
	t_exit					*exit;
	int						frame;
	t_animation_controller	*controller;

	if (!cube)
		return (CUBE_FALSE);
	exit = cube->entities->exit;
	if (!exit)
		return (CUBE_FALSE);
	controller = exit->base->controller;
	frame = controller->current->frame;
	if (controller->playing && frame != 0
		&& frame != controller->current->frames_ptr->frames_count - 1)
	{
		return (CUBE_TRUE);
	}
	return (CUBE_FALSE);
}
