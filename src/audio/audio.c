/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 17:10:14 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

t_audio_system	*audio_system_init(void)
{
    t_audio_system		*audio_system;
    ma_result			result;
    ma_engine_config	engineConfig;

    audio_system = malloc(sizeof(t_audio_system));
    if (!audio_system)
        return (NULL);    
    ft_memset(audio_system, 0, sizeof(t_audio_system));
    audio_system->masterVolume = 1.0f;
    engineConfig = ma_engine_config_init();
    result = ma_engine_init(&engineConfig, &audio_system->engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine: %d\n", result);
        free(audio_system);
        return (NULL);
    }
    result = ma_sound_group_init(&audio_system->engine, 0, NULL, &audio_system->musicGroup);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize music group: %d\n", result);
        ma_engine_uninit(&audio_system->engine);
        free(audio_system);
        return (NULL);
    }
    for (int i = 0; i < SOUND_COUNT; i++) {
        audio_system->soundLoaded[i] = FALSE;
        audio_system->decoders[i] = NULL;
    }
    audio_system->isPaused = FALSE;
    return (audio_system);
}

void	audio_system_shutdown(t_audio_system *audio_system)
{
    if (!audio_system)
        return;
    for (int i = 0; i < SOUND_COUNT; i++) {
        if (audio_system->soundLoaded[i]) {
            ma_sound_uninit(&audio_system->sounds[i]);
            if (audio_system->decoders[i] != NULL) {
                ma_decoder_uninit(audio_system->decoders[i]);
                free(audio_system->decoders[i]);
                audio_system->decoders[i] = NULL;
            }
        }
    }
    ma_sound_group_uninit(&audio_system->musicGroup);
    ma_engine_uninit(&audio_system->engine);
    free(audio_system);
}

t_bool	audio_load_sound(t_audio_system *audio_system, t_sound_type type, const char *filePath)
{
	ma_result	result;

    if (!audio_system || type >= SOUND_COUNT) {
        printf("Invalid sound type or audio system: %d\n", type);
        return (FALSE);
    }
    if (audio_system->soundLoaded[type]) {
        ma_sound_uninit(&audio_system->sounds[type]);
        if (audio_system->decoders[type] != NULL) {
            ma_decoder_uninit(audio_system->decoders[type]);
            free(audio_system->decoders[type]);
            audio_system->decoders[type] = NULL;
        }
        audio_system->soundLoaded[type] = FALSE;
    }
	audio_system->decoders[type] = (ma_decoder*)malloc(sizeof(ma_decoder));
	if (audio_system->decoders[type] == NULL) {
		printf("Failed to allocate memory for decoder\n");
		return (FALSE);
	}
	result = ma_decoder_init_file(filePath, NULL, audio_system->decoders[type]);
	if (result != MA_SUCCESS) {
		printf("Failed to initialize decoder for %s: %d\n", filePath, result);
		free(audio_system->decoders[type]);
		audio_system->decoders[type] = NULL;
		return (FALSE);
	}
    result = ma_sound_init_from_data_source(&audio_system->engine, audio_system->decoders[type], 
				MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, &audio_system->sounds[type]);   
	if (result != MA_SUCCESS) {
		printf("Failed to initialize sound from decoder: %d\n", result);
		ma_decoder_uninit(audio_system->decoders[type]);
		free(audio_system->decoders[type]);
		audio_system->decoders[type] = NULL;
		return (FALSE);
	}    
    if (result != MA_SUCCESS) {
        printf("Failed to load sound %s: %d\n", filePath, result);
        return (FALSE);
    }
    switch (type) {
        case SOUND_FOOTSTEPS:
            ma_sound_set_looping(&audio_system->sounds[type], TRUE);
            break;
        case SOUND_MUSIC_BACKGROUND:
        case SOUND_MUSIC_CREDITS:
            ma_sound_set_looping(&audio_system->sounds[type], TRUE);
            break;
        default:
            ma_sound_set_looping(&audio_system->sounds[type], FALSE);
            break;
    }
    audio_system->soundLoaded[type] = TRUE;
    return (TRUE);
}


static ma_result	audio_reset_sound(ma_sound* pSound)
{
    ma_result result;

    result = ma_sound_stop(pSound);
    if (result != MA_SUCCESS)
		return result;
    result = ma_sound_seek_to_pcm_frame(pSound, 0);
    if (result != MA_SUCCESS)
		return result;
    return (MA_SUCCESS);
}


void audio_play_sound(t_audio_system *audio_system, t_sound_type type, float volume)
{
    if (!audio_system || type >= SOUND_COUNT || !audio_system->soundLoaded[type]) {
        return;
    }
    if (type == SOUND_MUSIC_BACKGROUND || type == SOUND_MUSIC_CREDITS) {
        audio_play_music(audio_system, type, volume);
        return;
    }
    ma_sound_stop(&audio_system->sounds[type]);
    ma_sound_set_volume(&audio_system->sounds[type], volume * audio_system->masterVolume);
    ma_sound_start(&audio_system->sounds[type]);
}

void audio_stop_sound(t_audio_system *audio_system, t_sound_type type)
{
    if (!audio_system || type >= SOUND_COUNT || !audio_system->soundLoaded[type]) {
        return;
    }
	audio_reset_sound(&audio_system->sounds[type]);
}

void audio_play_music(t_audio_system *audio_system, t_sound_type musicType, float volume)
{
    if (!audio_system || (musicType != SOUND_MUSIC_BACKGROUND && musicType != SOUND_MUSIC_CREDITS) ||
        !audio_system->soundLoaded[musicType]) {
        return;
    }
    audio_stop_music(audio_system);
    ma_sound_set_volume(&audio_system->sounds[musicType], volume * audio_system->masterVolume);
    ma_sound_start(&audio_system->sounds[musicType]);
}

void audio_stop_music(t_audio_system *audio_system)
{
    if (!audio_system)
        return;
    ma_sound_group_stop(&audio_system->musicGroup);
}

void audio_set_master_volume(t_audio_system *audio_system, float volume)
{
    if (!audio_system)
        return;
    audio_system->masterVolume = volume;
    ma_engine_set_volume(&audio_system->engine, volume);
}

void audio_pause(t_audio_system *audio_system, t_bool pause)
{
    if (!audio_system || pause == audio_system->isPaused) {
        return ;
    }
    if (pause) {
        ma_engine_stop(&audio_system->engine);
    } else {
        ma_engine_start(&audio_system->engine);
    }
    audio_system->isPaused = pause;
}

t_bool is_sound_playing(t_audio_system *audio_system, t_sound_type type)
{
    if (!audio_system || type >= SOUND_COUNT || !audio_system->soundLoaded[type]) {
        return (FALSE);
    }
    return ma_sound_is_playing(&audio_system->sounds[type]);
}