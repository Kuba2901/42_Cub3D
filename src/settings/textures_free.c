/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 17:07:03 by jnenczak          #+#    #+#             */
/*   Updated: 2025/06/23 17:28:38 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_mlx_handler.h>
#include <stdlib.h>
#include <mlx.h>
#include <cube_settings.h>
#include <utils.h>
#include <libft.h>
#include <cube_mlx_handler.h>
#include <cube_settings_animated_sprites.h>
#include <parse_mandatory.h>
#include <cube_animations.h>

static void	settings_tex_free_frames(t_animated_frames *frames)
{
	int	i;

	if (!frames)
		return ;
	if (frames->frames)
	{
		i = 0;
		while (i < frames->frames_count)
		{
			safe_free(frames->frames[i]);
			i++;
		}
		safe_free(frames->frames);
	}
	safe_free(frames);
}

void	settings_tex_config_free(t_tex_config *tex_config)
{
	int	i;

	if (!tex_config)
		return ;
	if (tex_config->textures)
	{
		i = -1;
		while (++i < TEXTURE_TYPES_COUNT)
			safe_free(tex_config->textures[i]);
		safe_free(tex_config->textures);
	}
	settings_tex_free_frames(tex_config->enemy_frames);
	settings_tex_free_frames(tex_config->exit_idle_frames);
	settings_tex_free_frames(tex_config->exit_open_frames);
	safe_free(tex_config);
}
