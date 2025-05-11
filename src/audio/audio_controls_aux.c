/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_controls_aux.c                               :+:      :+:    :+:   */
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

void	audio_set_master_volume(t_audio_system *audio_system, float volume)
{
	if (!audio_system)
		return ;
	audio_system->master_volume = volume;
	ma_engine_set_volume(&audio_system->engine, volume);
}

void	audio_pause(t_audio_system *audio_system, t_bool pause)
{
	if (!audio_system || pause == audio_system->is_paused)
		return ;
	if (pause)
		ma_engine_stop(&audio_system->engine);
	else
		ma_engine_start(&audio_system->engine);
	audio_system->is_paused = pause;
}
