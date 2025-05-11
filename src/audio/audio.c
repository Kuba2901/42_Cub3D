/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:41:44 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_audio_system *audio_system_init(void)
{
    t_audio_system *audio_system;
    ma_result result;
    ma_engine_config engineConfig;

    audio_system = malloc(sizeof(t_audio_system));
    if (!audio_system)
        return (NULL);
    
    memset(audio_system, 0, sizeof(t_audio_system));
    audio_system->masterVolume = 1.0f;
    
    // Initialize miniaudio engine
    engineConfig = ma_engine_config_init();
    result = ma_engine_init(&engineConfig, &audio_system->engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine: %d\n", result);
        free(audio_system);
        return (NULL);
    }
    
    // Initialize sound group for music (for easy control)
    result = ma_sound_group_init(&audio_system->engine, 0, NULL, &audio_system->musicGroup);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize music group: %d\n", result);
        ma_engine_uninit(&audio_system->engine);
        free(audio_system);
        return (NULL);
    }
    
    // Mark all sounds as not loaded
    for (int i = 0; i < SOUND_COUNT; i++) {
        audio_system->soundLoaded[i] = FALSE;
        audio_system->decoders[i] = NULL;
    }
    
    audio_system->isPaused = FALSE;
    
    return (audio_system);
}

void audio_system_shutdown(t_audio_system *audio_system)
{
    if (!audio_system)
        return;
    
    // Stop all sounds
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
    
    // Uninitialize music group
    ma_sound_group_uninit(&audio_system->musicGroup);
    
    // Uninitialize engine
    ma_engine_uninit(&audio_system->engine);
    
    // Free audio system
    free(audio_system);
}

t_bool audio_load_sound(t_audio_system *audio_system, t_sound_type type, const char *filePath)
{
    if (!audio_system || type >= SOUND_COUNT) {
        printf("Invalid sound type or audio system: %d\n", type);
        return (FALSE);
    }
    
    // If sound was already loaded, unload it first
    if (audio_system->soundLoaded[type]) {
        ma_sound_uninit(&audio_system->sounds[type]);
        if (audio_system->decoders[type] != NULL) {
            ma_decoder_uninit(audio_system->decoders[type]);
            free(audio_system->decoders[type]);
            audio_system->decoders[type] = NULL;
        }
        audio_system->soundLoaded[type] = FALSE;
    }
    
    ma_result result;
    
    // For music types, we want to stream from disk rather than load entirely into memory
    if (type == SOUND_MUSIC_BACKGROUND || type == SOUND_MUSIC_CREDITS) {
        // Initialize sound with streaming
        result = ma_sound_init_from_file(&audio_system->engine, filePath, 
                                         MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_NO_SPATIALIZATION, 
                                         &audio_system->musicGroup, NULL, &audio_system->sounds[type]);
    } else {
        // For short sound effects, load entirely into memory
        // Allocate decoder
        audio_system->decoders[type] = (ma_decoder*)malloc(sizeof(ma_decoder));
        if (audio_system->decoders[type] == NULL) {
            printf("Failed to allocate memory for decoder\n");
            return (FALSE);
        }
        
        // Initialize decoder
        result = ma_decoder_init_file(filePath, NULL, audio_system->decoders[type]);
        if (result != MA_SUCCESS) {
            printf("Failed to initialize decoder for %s: %d\n", filePath, result);
            free(audio_system->decoders[type]);
            audio_system->decoders[type] = NULL;
            return (FALSE);
        }
        
        // Initialize sound from decoder
        result = ma_sound_init_from_data_source(&audio_system->engine, audio_system->decoders[type], 
                                               MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, &audio_system->sounds[type]);
        
        if (result != MA_SUCCESS) {
            printf("Failed to initialize sound from decoder: %d\n", result);
            ma_decoder_uninit(audio_system->decoders[type]);
            free(audio_system->decoders[type]);
            audio_system->decoders[type] = NULL;
            return (FALSE);
        }
    }
    
    if (result != MA_SUCCESS) {
        printf("Failed to load sound %s: %d\n", filePath, result);
        return (FALSE);
    }
    
    // Configure sound based on type
    switch (type) {
        case SOUND_FOOTSTEPS:
            // Set footsteps to loop by default
            ma_sound_set_looping(&audio_system->sounds[type], TRUE);
            break;
            
        case SOUND_MUSIC_BACKGROUND:
        case SOUND_MUSIC_CREDITS:
            // Set music to loop by default
            ma_sound_set_looping(&audio_system->sounds[type], TRUE);
            break;
            
        default:
            // Other sounds don't loop by default
            ma_sound_set_looping(&audio_system->sounds[type], FALSE);
            break;
    }
    
    audio_system->soundLoaded[type] = TRUE;
    return (TRUE);
}

void audio_play_sound(t_audio_system *audio_system, t_sound_type type, float volume)
{
    if (!audio_system || type >= SOUND_COUNT || !audio_system->soundLoaded[type]) {
        return;
    }
    
    // For music types, use audio_play_music instead
    if (type == SOUND_MUSIC_BACKGROUND || type == SOUND_MUSIC_CREDITS) {
        audio_play_music(audio_system, type, volume);
        return;
    }
    
    // Stop the sound first (in case it's already playing)
    ma_sound_stop(&audio_system->sounds[type]);
    
    // Set volume
    ma_sound_set_volume(&audio_system->sounds[type], volume * audio_system->masterVolume);
    
    // Start playing
    ma_sound_start(&audio_system->sounds[type]);
}

void audio_stop_sound(t_audio_system *audio_system, t_sound_type type)
{
    if (!audio_system || type >= SOUND_COUNT || !audio_system->soundLoaded[type]) {
        return;
    }
    
    ma_sound_stop(&audio_system->sounds[type]);
}

void audio_play_music(t_audio_system *audio_system, t_sound_type musicType, float volume)
{
    if (!audio_system || (musicType != SOUND_MUSIC_BACKGROUND && musicType != SOUND_MUSIC_CREDITS) ||
        !audio_system->soundLoaded[musicType]) {
        return;
    }
    
    // Stop any currently playing music
    audio_stop_music(audio_system);
    
    // Set volume
    ma_sound_set_volume(&audio_system->sounds[musicType], volume * audio_system->masterVolume);
    
    // Start playing
    ma_sound_start(&audio_system->sounds[musicType]);
}

void audio_stop_music(t_audio_system *audio_system)
{
    if (!audio_system)
        return;
        
    // Stop all sounds in the music group
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
        return;  // Already in requested state or invalid audio system
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