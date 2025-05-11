/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 19:58:18 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/11 16:16:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_mlx_handler.h>
#include <cube_animations.h>
#include <libft.h>

t_enemy	*entities_enemy_init(t_point pt, t_animated_frames *frames_ptr)
{
	t_enemy	*enemy;

	enemy = malloc(sizeof(t_enemy));
	if (!enemy)
		return (NULL);
	enemy->base = entities_entity_init(pt, ENTITY_TYPE_ENEMY, frames_ptr);
	if (!enemy->base)
	{
		safe_free(enemy);
		return (NULL);
	}
	enemy->base->controller->playing = CUBE_TRUE;
	enemy->base->controller->repeat = CUBE_TRUE;
	return (enemy);
}

void	entities_enemy_free(t_enemy *enemy)
{
	if (!enemy)
		return ;
	entities_entity_free(enemy->base);
	safe_free(enemy);
}

t_enemy	**entities_enemies_multiple_init(t_point **enemy_locations,
	t_animated_frames *frames_ptr)
{
	t_enemy	**enemies;
	int		i;

	i = -1;
	if (!enemy_locations)
		return (NULL);
	while (enemy_locations[++i] != NULL)
		;
	enemies = malloc(sizeof(t_enemy *) * (i + 1));
	if (!enemies)
		return (NULL);
	i = -1;
	while (enemy_locations[++i] != NULL)
		enemies[i] = entities_enemy_init(*enemy_locations[i], frames_ptr);
	enemies[i] = NULL;
	return (enemies);
}

void	entities_enemies_multiple_free(t_enemy **enemies)
{
	int	i;

	if (!enemies)
		return ;
	i = -1;
	while (enemies[++i] != NULL)
		entities_enemy_free(enemies[i]);
	safe_free(enemies);
	enemies = NULL;
}
