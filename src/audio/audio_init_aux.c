/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_init_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:09:10 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <cube.h>

static t_bool	audio_init_sound(t_audio_system *audio_system,
	t_sound_type type)
{
	ma_result	result;

	result = ma_sound_init_from_data_source(&audio_system->engine,
			audio_system->decoders[type], MA_SOUND_FLAG_NO_SPATIALIZATION,
			NULL, &audio_system->sounds[type]);
	if (result != MA_SUCCESS)
	{
		printf("Failed to initialize sound from decoder: %d\n", result);
		ma_decoder_uninit(audio_system->decoders[type]);
		free(audio_system->decoders[type]);
		audio_system->decoders[type] = NULL;
		return (CUBE_FALSE);
	}
	return (CUBE_TRUE);
}

static void	audio_configure_sound_properties(t_audio_system *audio_system,
	t_sound_type type)
{
	if (type == SOUND_FOOTSTEPS || type == SOUND_MUSIC_BACKGROUND
		|| type == SOUND_MUSIC_CREDITS)
		ma_sound_set_looping(&audio_system->sounds[type], CUBE_TRUE);
	else
		ma_sound_set_looping(&audio_system->sounds[type], CUBE_FALSE);
	audio_system->sound_loaded[type] = CUBE_TRUE;
}

t_bool	audio_load_sound(t_audio_system *audio_system, t_sound_type type,
	const char *filePath)
{
	if (!audio_system || type >= SOUND_COUNT)
	{
		printf("Invalid sound type or audio system: %d\n", type);
		return (CUBE_FALSE);
	}
	audio_uninit_existing_sound(audio_system, type);
	if (!audio_init_decoder(audio_system, type, filePath))
		return (CUBE_FALSE);
	if (!audio_init_sound(audio_system, type))
		return (CUBE_FALSE);
	audio_configure_sound_properties(audio_system, type);
	return (CUBE_TRUE);
}

static t_bool	load_game_sounds(t_audio_system *audio_system)
{
	t_bool	success;

	success = CUBE_TRUE;
	success &= audio_load_sound(audio_system, SOUND_FOOTSTEPS,
			"./assets/sounds/footsteps.wav");
	success &= audio_load_sound(audio_system, SOUND_ELEVATOR_OPEN,
			"./assets/sounds/elevator_door.wav");
	success &= audio_load_sound(audio_system, SOUND_ELEVATOR_CLOSE,
			"./assets/sounds/elevator_door.wav");
	success &= audio_load_sound(audio_system, SOUND_COLLECTIBLE,
			"./assets/sounds/collectible.wav");
	success &= audio_load_sound(audio_system, SOUND_MUSIC_BACKGROUND,
			"./assets/sounds/background_music.mp3");
	success &= audio_load_sound(audio_system, SOUND_MUSIC_CREDITS,
			"./assets/sounds/credits_music.mp3");
	if (!success)
		printf("Warning: Some sounds failed to load\n");
	return (success);
}

void	audio_init_start_bg_music(t_audio_system *audio_system)
{
	if (load_game_sounds(audio_system))
	{
		audio_play_music(audio_system, SOUND_MUSIC_BACKGROUND, AUDIO_MUSIC_VOL);
		printf("Started background music...\n");
	}
}
