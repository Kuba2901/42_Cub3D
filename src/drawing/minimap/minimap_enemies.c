/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_enemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:43:20 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 19:38:18 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_drawing.h>
#include <cube_minimap.h>
#include <cube_entities.h>
#include <cube.h>
#include <cube_mlx_handler.h>

static void	minimap_draw_single_enemy_circle(t_minimap_data *mmd)
{
	int	px;
	int	py;
	int	x;
	int	y;

	y = -MINIMAP_ENEMY_SIZE - 1;
	while (++y <= MINIMAP_ENEMY_SIZE)
	{
		x = -MINIMAP_ENEMY_SIZE - 1;
		while (++x <= MINIMAP_ENEMY_SIZE)
		{
			if (x * x + y * y <= MINIMAP_ENEMY_SIZE * MINIMAP_ENEMY_SIZE)
			{
				px = mmd->screen_x + x;
				py = mmd->screen_y + y;
				if (px >= mmd->minimap_pos_x
					&& px < mmd->minimap_pos_x + MINIMAP_SIZE
					&& py >= mmd->minimap_pos_y
					&& py < mmd->minimap_pos_y + MINIMAP_SIZE)
					draw_my_mlx_pixel_put(mmd->img, px, py, DRAW_RED_COLOR);
			}
		}
	}
}

static void	minimap_draw_single_enemy(t_minimap_data *mmd,
	t_enemy **enemies, int i)
{
	int	enemy_map_x;
	int	enemy_map_y;

	enemy_map_x = (int)enemies[i]->base->current_location.x;
	enemy_map_y = (int)enemies[i]->base->current_location.y;
	if (abs(enemy_map_x - mmd->map_center_x) <= mmd->map_radius
		&& abs(enemy_map_y - mmd->map_center_y) <= mmd->map_radius)
	{
		mmd->screen_x = mmd->minimap_pos_x
			+ (enemy_map_x - mmd->map_center_x + mmd->map_radius)
			* MINIMAP_CELL_SIZE;
		mmd->screen_y = mmd->minimap_pos_y
			+ (enemy_map_y - mmd->map_center_y + mmd->map_radius)
			* MINIMAP_CELL_SIZE;
		minimap_draw_single_enemy_circle(mmd);
	}
}

void	minimap_draw_enemies(t_minimap_data *mmd)
{
	t_cube	*cube;
	t_enemy	**enemies;
	int		i;

	cube = mmd->cube;
	enemies = cube->entities->enemies;
	i = 0;
	if (!enemies)
		return ;
	while (enemies[i] != NULL)
	{
		minimap_draw_single_enemy(mmd, enemies, i);
		i++;
	}
}
