/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:22:53 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:37:48 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_entities.h>
#include <cube_settings.h>
#include <cube_settings_map.h>
#include <cube.h>
#include <cube_drawing.h>
#include <cube_animations.h>
#include <cube_settings_animated_sprites.h>
#include <math.h>
#include <stdlib.h>
#include <cube_sprites.h>

static int	sprite_count_enemies(t_enemy **enemies)
{
	int	count;

	count = 0;
	if (!enemies)
		return (0);
	while (enemies[count] != NULL)
		count++;
	return (count);
}

static void	sprite_calculate_distances(t_enemy **enemies,
			t_entities *entities, int num_sprites)
{
	int	i;

	i = 0;
	while (i < num_sprites)
	{
		entities->sprite_order[i] = i;
		entities->sprite_distance[i] = sprite_get_distance(
				enemies[i], entities->player);
		i++;
	}
	sprite_sort(entities->sprite_order,
		entities->sprite_distance, num_sprites);
}

static void	sprite_draw(t_cube *cube, t_enemy *sprite)
{
	t_sprite_data	data;
	t_player		*player;

	player = cube->entities->player;
	sprite_calculate_position(sprite, player, &data);
	sprite_calculate_dimensions(&data);
	sprite_process(cube, sprite, &data);
}

void	sprites_draw(t_cube *cube)
{
	t_entities	*entities;
	t_enemy		**enemies;
	int			num_sprites;
	int			i;

	entities = cube->entities;
	enemies = entities->enemies;
	num_sprites = sprite_count_enemies(enemies);
	if (num_sprites == 0)
		return ;
	sprite_calculate_distances(enemies, entities, num_sprites);
	i = 0;
	while (i < num_sprites)
	{
		sprite_draw(cube, enemies[entities->sprite_order[i]]);
		i++;
	}
}
