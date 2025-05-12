/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:58:18 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:15:39 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_mlx_handler.h>
#include <cube_animations.h>
#include <libft.h>

t_entities	*entities_entities_init(t_entities_config config)
{
	t_entities	*entities;

	entities = entities_allocate();
	if (!entities)
		return (NULL);
	if (!entities_init_exit(entities, config)
		|| !entities_init_enemies(entities, config)
		|| !entities_init_player(entities, config))
	{
		entities_entities_free(entities);
		return (NULL);
	}
	if (!entities_allocate_sprites(entities, config.enemies_count))
	{
		entities_entities_free(entities);
		return (NULL);
	}
	return (entities);
}

void	entities_entities_free(t_entities *entities)
{
	if (!entities)
		return ;
	entities_enemies_multiple_free(entities->enemies);
	entities_player_free(entities->player);
	entities_exit_free(entities->exit);
	safe_free(entities->sprite_order);
	safe_free(entities->sprite_distance);
	safe_free(entities);
}

t_entities_config	entities_entities_config_init(
	t_cube_settings *cube_settings)
{
	t_entities_config	entities_config;

	entities_config.enemies_locations
		= cube_settings->map_config->enemies_locations;
	entities_config.enemies_count = cube_settings->map_config->enemies_count;
	entities_config.player_location = cube_settings->map_config->start_location;
	entities_config.enemy_frames_ptr = cube_settings->tex_config->enemy_frames;
	entities_config.exit_idle_frames_ptr
		= cube_settings->tex_config->exit_idle_frames;
	entities_config.exit_open_frames_ptr
		= cube_settings->tex_config->exit_open_frames;
	entities_config.exit_location = cube_settings->map_config->exit_location;
	printf("Entities configuration initialized successfully.\n");
	return (entities_config);
}
