/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:58:18 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:14:16 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_mlx_handler.h>
#include <cube_animations.h>
#include <libft.h>

static t_vector	entities_player_get_orientation(t_point pt)
{
	t_vector	ret;

	if (pt.c == 'N')
	{
		ret.dir_x = 0;
		ret.dir_y = -1;
	}
	else if (pt.c == 'S')
	{
		ret.dir_x = 0;
		ret.dir_y = 1;
	}
	else if (pt.c == 'E')
	{
		ret.dir_x = 1;
		ret.dir_y = 0;
	}
	else
	{
		ret.dir_x = -1;
		ret.dir_y = 0;
	}
	return (ret);
}

t_player	*entities_player_init(t_point pt)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		return (NULL);
	player->base = entities_entity_init(pt, ENTITY_TYPE_PLAYER, NULL);
	if (!player->base)
	{
		safe_free(player);
		return (NULL);
	}
	player->dir = entities_player_get_orientation(pt);
	player->camera.dir_x = player->dir.dir_y * FOV;
	player->camera.dir_y = -player->dir.dir_x * FOV;
	return (player);
}

void	entities_player_free(t_player *player)
{
	if (!player)
		return ;
	safe_free(player->base);
	free(player);
}
