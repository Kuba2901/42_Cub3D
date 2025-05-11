/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:09:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

static ma_result	audio_reset_sound(ma_sound *p_sound)
{
	ma_result	result;

	result = ma_sound_stop(p_sound);
	if (result != MA_SUCCESS)
		return (result);
	result = ma_sound_seek_to_pcm_frame(p_sound, 0);
	if (result != MA_SUCCESS)
		return (result);
	return (MA_SUCCESS);
}

void	audio_play_sound(t_audio_system *audio_system, t_sound_type type,
	float volume)
{
	if (!audio_system
		|| type >= SOUND_COUNT
		|| !audio_system->sound_loaded[type])
		return ;
	if (type == SOUND_MUSIC_BACKGROUND || type == SOUND_MUSIC_CREDITS)
	{
		audio_play_music(audio_system, type, volume);
		return ;
	}
	ma_sound_stop(&audio_system->sounds[type]);
	ma_sound_set_volume(&audio_system->sounds[type],
		volume * audio_system->master_volume);
	ma_sound_start(&audio_system->sounds[type]);
}

void	audio_stop_sound(t_audio_system *audio_system, t_sound_type type)
{
	if (!audio_system || type >= SOUND_COUNT
		|| !audio_system->sound_loaded[type])
		return ;
	audio_reset_sound(&audio_system->sounds[type]);
}

void	audio_play_music(t_audio_system *audio_system,
	t_sound_type musicType, float volume)
{
	if (!audio_system
		|| (musicType != SOUND_MUSIC_BACKGROUND
			&& musicType != SOUND_MUSIC_CREDITS)
		|| !audio_system->sound_loaded[musicType])
		return ;
	audio_stop_music(audio_system);
	ma_sound_set_volume(&audio_system->sounds[musicType],
		volume * audio_system->master_volume);
	ma_sound_start(&audio_system->sounds[musicType]);
}

void	audio_stop_music(t_audio_system *audio_system)
{
	if (!audio_system)
		return ;
	ma_sound_group_stop(&audio_system->music_group);
}
