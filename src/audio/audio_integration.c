/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_integration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:55:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 17:03:20 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_audio.h>
#include <cube_entities.h>
#include <cube_input_handler.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>

void	audio_update_player_movement(t_cube *cube)
{
	t_bool is_moving;
	
	// No audio system or not loaded
	if (!cube->audio_system || !cube->audio_system->soundLoaded[SOUND_FOOTSTEPS])
		return;
	
	// Check if player is moving
	is_moving = cube->input_handler->keys->w || 
				cube->input_handler->keys->a || 
				cube->input_handler->keys->s || 
				cube->input_handler->keys->d;
	
	// Handle footstep sounds
	if (is_moving)
	{
		// Start footsteps if not already playing
		if (!is_sound_playing(cube->audio_system, SOUND_FOOTSTEPS))
			audio_play_sound(cube->audio_system, SOUND_FOOTSTEPS, 0.8f);
	}
	else
	{
		// Stop footsteps if player stops moving
		if (is_sound_playing(cube->audio_system, SOUND_FOOTSTEPS))
			audio_stop_sound(cube->audio_system, SOUND_FOOTSTEPS);
	}
}

void	audio_handle_collectible(t_cube *cube)
{
	// No audio system or not loaded
	if (!cube->audio_system || !cube->audio_system->soundLoaded[SOUND_COLLECTIBLE])
		return;
	
	// Play collectible sound
	audio_play_sound(cube->audio_system, SOUND_COLLECTIBLE, 1.0f);
}

void	audio_handle_elevator(t_cube *cube, t_bool is_opening)
{	
	if (!cube->audio_system)
		return;	
	if (!is_opening)
	{
		audio_stop_sound(cube->audio_system, SOUND_ELEVATOR_OPEN);
		return ;
	}
	if (cube->audio_system->soundLoaded[SOUND_ELEVATOR_OPEN])
		audio_play_sound(cube->audio_system, SOUND_ELEVATOR_OPEN, AUDIO_SFX_VOL);
}

static t_bool	audio_elevator_in_motion(t_cube *cube)
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

void	audio_integration_handle_exit(t_cube *cube)
{
	int	i;

	if (!cube->audio_system)
		return ;
	i = -1;
	audio_stop_music(cube->audio_system);
	while (++i < SOUND_COUNT - 1)
	{
		if (i == SOUND_MUSIC_CREDITS)
			continue ;
		audio_stop_sound(cube->audio_system, i);
	}
	audio_play_music(cube->audio_system, SOUND_MUSIC_CREDITS, AUDIO_MUSIC_VOL);		
}

void	audio_integration_update(t_cube *cube)
{
	if (!cube->audio_system)
		return;
	audio_update_player_movement(cube);
	audio_handle_elevator(cube, audio_elevator_in_motion(cube));
}