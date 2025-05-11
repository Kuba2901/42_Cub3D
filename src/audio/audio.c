/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:09:10 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#
#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

void	audio_system_shutdown(t_audio_system *audio_system)
{
	int	i;

	if (!audio_system)
		return ;
	audio_stop_music(audio_system);
	i = -1;
	while (++i < SOUND_COUNT)
	{
		if (audio_system->sound_loaded[i])
		{
			ma_sound_stop(&audio_system->sounds[i]);
			ma_sound_uninit(&audio_system->sounds[i]);
			if (audio_system->decoders[i])
			{
				ma_decoder_uninit(audio_system->decoders[i]);
				free(audio_system->decoders[i]);
				audio_system->decoders[i] = NULL;
			}
		}
	}
	ma_sound_group_uninit(&audio_system->music_group);
	ma_engine_uninit(&audio_system->engine);
	free(audio_system);
}
