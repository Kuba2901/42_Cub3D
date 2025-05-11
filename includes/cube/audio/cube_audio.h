/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_audio.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:14:03 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_AUDIO_H
# define CUBE_AUDIO_H

# include <utils.h>
# include "miniaudio.h"

typedef enum e_sound_type
{
    SOUND_FOOTSTEPS,
    SOUND_ELEVATOR_OPEN,
    SOUND_ELEVATOR_CLOSE,
    SOUND_COLLECTIBLE,
    SOUND_MUSIC_BACKGROUND,
    SOUND_MUSIC_CREDITS,
    SOUND_COUNT
} t_sound_type;

typedef struct s_audio_system
{
    ma_engine		engine;
    ma_sound		sounds[SOUND_COUNT];
    ma_sound_group	musicGroup;
    ma_decoder		*decoders[SOUND_COUNT];
    t_bool			soundLoaded[SOUND_COUNT];
    float			masterVolume;
    t_bool			isPaused;
}	t_audio_system;

// Initialize the audio system
t_audio_system	*audio_system_init(void);

// Clean up and free resources
void			audio_system_shutdown(t_audio_system *audio_system);

// Load a sound from a file path
t_bool			audio_load_sound(t_audio_system *audio_system, t_sound_type type, const char *filePath);

// Play a sound effect
void			audio_play_sound(t_audio_system *audio_system, t_sound_type type, float volume);

// Stop a specific sound
void			audio_stop_sound(t_audio_system *audio_system, t_sound_type type);

// Play music (looping)
void			audio_play_music(t_audio_system *audio_system, t_sound_type musicType, float volume);

// Stop all music
void			audio_stop_music(t_audio_system *audio_system);

// Set global volume (0.0 to 1.0)
void			audio_set_master_volume(t_audio_system *audio_system, float volume);

// Pause/resume all audio
void			audio_pause(t_audio_system *audio_system, t_bool pause);

// Check if a sound is currently playing
t_bool			is_sound_playing(t_audio_system *audio_system, t_sound_type type);

#endif