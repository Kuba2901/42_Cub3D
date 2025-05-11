/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_audio.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:10:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_AUDIO_H
# define CUBE_AUDIO_H

# include <utils.h>
# include <miniaudio.h>

# define AUDIO_MUSIC_VOL 0.1f
# define AUDIO_SFX_VOL 0.3f
# define AUDIO_MASTER_VOL 1.0f

typedef enum e_sound_type
{
	SOUND_FOOTSTEPS,
	SOUND_ELEVATOR_OPEN,
	SOUND_ELEVATOR_CLOSE,
	SOUND_COLLECTIBLE,
	SOUND_MUSIC_BACKGROUND,
	SOUND_MUSIC_CREDITS,
	SOUND_COUNT
}	t_sound_type;

typedef struct s_audio_system
{
	ma_engine		engine;
	ma_sound		sounds[SOUND_COUNT];
	ma_sound_group	music_group;
	ma_decoder		*decoders[SOUND_COUNT];
	t_bool			sound_loaded[SOUND_COUNT];
	float			master_volume;
	t_bool			is_paused;
}	t_audio_system;

typedef struct s_cube	t_cube;

t_audio_system	*audio_system_init(void);
void			audio_system_shutdown(t_audio_system *audio_system);
t_bool			audio_load_sound(t_audio_system *audio_system,
					t_sound_type type, const char *filePath);
void			audio_play_sound(t_audio_system *audio_system,
					t_sound_type type, float volume);
void			audio_stop_sound(t_audio_system *audio_system,
					t_sound_type type);
void			audio_play_music(t_audio_system *audio_system,
					t_sound_type musicType, float volume);
void			audio_stop_music(t_audio_system *audio_system);
void			audio_set_master_volume(t_audio_system *audio_system,
					float volume);
void			audio_pause(t_audio_system *audio_system, t_bool pause);
t_bool			audio_is_sound_playing(t_audio_system *audio_system,
					t_sound_type type);
void			audio_init_start_bg_music(t_audio_system *audio_system);
t_bool			audio_init_decoder(t_audio_system *audio_system,
					t_sound_type type, const char *filePath);
void			audio_uninit_existing_sound(t_audio_system *audio_system,
					t_sound_type type);
t_bool			audio_elevator_in_motion(t_cube *cube);
void			audio_handle_elevator(t_cube *cube, t_bool is_opening);
void			audio_update_player_movement(t_cube *cube);

#endif