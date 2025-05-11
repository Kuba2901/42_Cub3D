/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 21:10:14 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>

t_bool	audio_is_sound_playing(t_audio_system *audio_system, t_sound_type type)
{
	if (!audio_system || type >= SOUND_COUNT
		|| !audio_system->sound_loaded[type])
	{
		return (CUBE_FALSE);
	}
	return (ma_sound_is_playing(&audio_system->sounds[type]));
}
