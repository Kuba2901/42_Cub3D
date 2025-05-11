/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_integration_aux.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 15:22:30 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 19:23:02 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_audio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libft.h>
#include <cube.h>

void	audio_integration_handle_exit(t_cube *cube)
{
	int	i;

	if (!cube->audio_system)
		return ;
	i = -1;
	audio_stop_music(cube->audio_system);
	while (++i < SOUND_COUNT - 1)
	{
		if (i == SOUND_MUSIC_CREDITS)
			continue ;
		audio_stop_sound(cube->audio_system, i);
	}
	audio_play_music(cube->audio_system, SOUND_MUSIC_CREDITS,
		AUDIO_MUSIC_VOL);
}

void	audio_integration_update(t_cube *cube)
{
	if (!cube->audio_system)
		return ;
	audio_update_player_movement(cube);
	audio_handle_elevator(cube, audio_elevator_in_motion(cube));
}
