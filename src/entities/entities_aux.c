/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:58:18 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:16:55 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_mlx_handler.h>
#include <cube_animations.h>
#include <libft.h>

t_entities	*entities_allocate(void)
{
	t_entities	*entities;

	entities = malloc(sizeof(t_entities));
	if (!entities)
		return (NULL);
	entities->enemies = NULL;
	entities->sprite_order = NULL;
	entities->sprite_distance = NULL;
	return (entities);
}

int	entities_init_exit(t_entities *entities, t_entities_config config)
{
	entities->exit = entities_exit_init(config.exit_location,
			config.exit_idle_frames_ptr, config.exit_open_frames_ptr);
	if (!entities->exit)
		return (0);
	return (1);
}

int	entities_init_enemies(t_entities *entities, t_entities_config config)
{
	if (config.enemies_locations != NULL)
	{
		entities->enemies = entities_enemies_multiple_init(
				config.enemies_locations, config.enemy_frames_ptr);
		if (!entities->enemies)
			return (0);
	}
	return (1);
}

int	entities_init_player(t_entities *entities, t_entities_config config)
{
	entities->player = entities_player_init(config.player_location);
	if (!entities->player)
		return (0);
	return (1);
}

int	entities_allocate_sprites(t_entities *entities, int num_enemies)
{
	if (num_enemies > 0)
	{
		entities->sprite_order = malloc(sizeof(int) * num_enemies);
		entities->sprite_distance = malloc(sizeof(double) * num_enemies);
		if (!entities->sprite_order || !entities->sprite_distance)
			return (0);
	}
	return (1);
}
