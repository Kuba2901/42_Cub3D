/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_cells.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:43:20 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 19:34:17 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_drawing.h>
#include <cube_minimap.h>
#include <cube_entities.h>
#include <cube.h>
#include <cube_mlx_handler.h>

static void	minimap_cells_draw_single_cell(t_minimap_data *mmd, int color)
{
	int	px;
	int	py;
	int	cy;
	int	cx;

	cy = -1;
	while (++cy < MINIMAP_CELL_SIZE - 1)
	{
		cx = -1;
		while (++cx < MINIMAP_CELL_SIZE - 1)
		{
			px = mmd->screen_x + cx;
			py = mmd->screen_y + cy;
			if (px >= mmd->minimap_pos_x
				&& px < mmd->minimap_pos_x + MINIMAP_SIZE
				&& py >= mmd->minimap_pos_y
				&& py < mmd->minimap_pos_y + MINIMAP_SIZE)
				draw_my_mlx_pixel_put(mmd->img, px, py, color);
		}
	}
}

void	minimap_draw_cells(t_minimap_data *mmd)
{
	int		y;
	int		x;
	int		color;

	y = -mmd->map_radius - 1;
	while (++y <= mmd->map_radius)
	{
		x = -mmd->map_radius - 1;
		while (++x <= mmd->map_radius)
		{
			mmd->map_x = mmd->map_center_x + x;
			mmd->map_y = mmd->map_center_y + y;
			if (mmd->map_x < 0 || mmd->map_x >= mmd->cube->map->width
				|| mmd->map_y < 0 || mmd->map_y >= mmd->cube->map->height)
				continue ;
			mmd->screen_x = mmd->minimap_pos_x
				+ (x + mmd->map_radius) * MINIMAP_CELL_SIZE;
			mmd->screen_y = mmd->minimap_pos_y
				+ (y + mmd->map_radius) * MINIMAP_CELL_SIZE;
			color = MINIMAP_FLOOR_COLOR;
			if (mmd->cube->map->tiles[mmd->map_y][mmd->map_x].c == '1')
				color = MINIMAP_WALL_COLOR;
			minimap_cells_draw_single_cell(mmd, color);
		}
	}
}
