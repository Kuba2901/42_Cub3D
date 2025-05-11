/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:09:22 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#
#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

static ma_result	audio_system_init_engine(t_audio_system *audio_system)
{
	ma_result			result;
	ma_engine_config	engine_config;

	engine_config = ma_engine_config_init();
	result = ma_engine_init(&engine_config, &audio_system->engine);
	if (result != MA_SUCCESS)
	{
		printf("Failed to initialize audio engine: %d\n", result);
		free(audio_system);
	}
	return (result);
}

static ma_result	audio_system_init_sound_group(t_audio_system *audio_system)
{
	ma_result			result;

	result = ma_sound_group_init(&audio_system->engine, 0, NULL,
			&audio_system->music_group);
	if (result != MA_SUCCESS)
	{
		printf("Failed to initialize music group: %d\n", result);
		ma_engine_uninit(&audio_system->engine);
		free(audio_system);
	}
	return (result);
}

t_audio_system	*audio_system_init(void)
{
	t_audio_system		*audio_system;
	ma_result			result;
	int					i;

	audio_system = malloc(sizeof(t_audio_system));
	if (!audio_system)
		return (NULL);
	ft_memset(audio_system, 0, sizeof(t_audio_system));
	audio_system->master_volume = AUDIO_MASTER_VOL;
	result = audio_system_init_engine(audio_system);
	if (result != MA_SUCCESS)
		return (NULL);
	result = audio_system_init_sound_group(audio_system);
	if (result != MA_SUCCESS)
		return (NULL);
	i = -1;
	while (++i < SOUND_COUNT)
	{
		audio_system->sound_loaded[i] = CUBE_FALSE;
		audio_system->decoders[i] = NULL;
	}
	audio_system->is_paused = CUBE_FALSE;
	audio_init_start_bg_music(audio_system);
	return (audio_system);
}

void	audio_uninit_existing_sound(t_audio_system *audio_system,
	t_sound_type type)
{
	if (audio_system->sound_loaded[type])
	{
		ma_sound_uninit(&audio_system->sounds[type]);
		if (audio_system->decoders[type] != NULL)
		{
			ma_decoder_uninit(audio_system->decoders[type]);
			free(audio_system->decoders[type]);
			audio_system->decoders[type] = NULL;
		}
		audio_system->sound_loaded[type] = CUBE_FALSE;
	}
}

t_bool	audio_init_decoder(t_audio_system *audio_system,
								t_sound_type type, const char *filePath)
{
	ma_result	result;

	audio_system->decoders[type] = (ma_decoder *)malloc(sizeof(ma_decoder));
	if (audio_system->decoders[type] == NULL)
	{
		printf("Failed to allocate memory for decoder\n");
		return (CUBE_FALSE);
	}
	result = ma_decoder_init_file(filePath, NULL, audio_system->decoders[type]);
	if (result != MA_SUCCESS)
	{
		printf("Failed to initialize decoder for %s: %d\n", filePath, result);
		free(audio_system->decoders[type]);
		audio_system->decoders[type] = NULL;
		return (CUBE_FALSE);
	}
	return (CUBE_TRUE);
}
