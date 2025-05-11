/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:50:58 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:36:12 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_settings.h>
#include <cube_entities.h>
#include <cube_input_handler.h>
#include <cube_mlx_handler.h>
#include <cube_runtime.h>
#include <cube_dda.h>
#include <cube_audio.h>
#include <stdio.h>
#include <cube_drawing.h>

// Function to load all game sounds
static t_bool	load_game_sounds(t_audio_system *audio_system)
{
	t_bool success;

	success = CUBE_TRUE;
	
	// Load all game sounds
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

t_cube	*cube_cube_init(char **map, int width, int height,
	const char **tex_paths)
{
	t_cube	*cube;

	cube = malloc(sizeof(t_cube));
	if (!cube)
		return (NULL);
	printf("1... Allocated memory for cube\n");
	cube->mlx_handler = mlx_mlx_handler_init();
	printf("2... Initialized mlx_handler\n");
	cube->cube_settings = settings_cube_init(
			settings_map_config_init(map, width, height),
			settings_tex_config_init(tex_paths, cube->mlx_handler));
	printf("3... Initialized cube_settings\n");
	cube->entities = entities_entities_init(
			entities_entities_config_init(cube->cube_settings));
	printf("4... Initialized entities\n");
	cube->map = map_map_init(cube->cube_settings->map_config);
	printf("5... Initialized map\n");
	cube->runtime_handler = runtime_runtime_handler_init();
	printf("6... Initialized runtime_handler\n");
	cube->input_handler = input_handler_init();
	printf("7... Initialized input_handler\n");
	cube->dda_data = dda_init();
	printf("8... Initialized DDA data\n");
	cube->audio_system = audio_system_init();
	printf("9... Initialized audio system\n");
	if (cube->audio_system)
	{
		if (load_game_sounds(cube->audio_system))
		{
			// Start background music
			audio_play_music(cube->audio_system, SOUND_MUSIC_BACKGROUND, 0.8f);
			printf("10... Started background music\n");
		}
	}
	return (cube);
}

void	cube_cube_free(t_cube *cube)
{
	if (cube->runtime_handler->display_credits)
	{
		if (cube->audio_system && !is_sound_playing(cube->audio_system, SOUND_MUSIC_CREDITS))
			audio_play_music(cube->audio_system, SOUND_MUSIC_CREDITS, 0.8f);
		credits_display(cube);
	}
	cube->runtime_handler->running = CUBE_FALSE;
	map_map_free(cube->map);
	input_handler_free(cube->input_handler);
	entities_entities_free(cube->entities);
	settings_cube_free(cube->cube_settings);
	if (cube->audio_system)
		audio_system_shutdown(cube->audio_system);
	mlx_mlx_handler_free(cube->mlx_handler);
	runtime_runtime_handler_free(cube->runtime_handler);
	dda_free(cube->dda_data);
	safe_free(cube);
	exit(EXIT_SUCCESS);
}