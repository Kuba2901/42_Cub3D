/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:43:20 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 19:30:01 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_drawing.h>
#include <cube_minimap.h>
#include <cube_entities.h>
#include <cube.h>
#include <cube_mlx_handler.h>

void	minimap_draw_border(t_minimap_data *mmd)
{
	int	y;
	int	x;

	y = -1;
	while (++y < MINIMAP_SIZE + 2)
	{
		x = -1;
		while (++x < MINIMAP_SIZE + 2)
		{
			if (x == 0 || y == 0 || x == MINIMAP_SIZE + 1
				|| y == MINIMAP_SIZE + 1)
			{
				mmd->screen_x = mmd->minimap_pos_x - 1 + x;
				mmd->screen_y = mmd->minimap_pos_y - 1 + y;
				if (mmd->screen_x >= 0 && mmd->screen_x < WINDOW_WIDTH
					&& mmd->screen_y >= 0 && mmd->screen_y < WINDOW_HEIGHT)
					draw_my_mlx_pixel_put(mmd->img, mmd->screen_x,
						mmd->screen_y, MINIMAP_BORDER_COLOR);
			}
		}
	}
}

static void	minimap_draw_background(t_minimap_data *mmd)
{
	int	y;
	int	x;

	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
		while (++x < MINIMAP_SIZE)
		{
			mmd->screen_x = mmd->minimap_pos_x + x;
			mmd->screen_y = mmd->minimap_pos_y + y;
			if (mmd->screen_x >= 0 && mmd->screen_x < WINDOW_WIDTH
				&& mmd->screen_y >= 0 && mmd->screen_y < WINDOW_HEIGHT)
				draw_my_mlx_pixel_put(mmd->img, mmd->screen_x,
					mmd->screen_y, MINIMAP_BACKGROUND_COLOR);
		}
	}
}

void	draw_minimap(t_cube *cube)
{
	t_minimap_data	mmd;

	mmd.minimap_pos_x = WINDOW_WIDTH - MINIMAP_SIZE - MINIMAP_MARGIN;
	mmd.minimap_pos_y = MINIMAP_MARGIN;
	mmd.player = cube->entities->player;
	mmd.img = cube->mlx_handler->mlx_img;
	mmd.cube = cube;
	minimap_draw_border(&mmd);
	minimap_draw_background(&mmd);
	mmd.map_center_x = (int)mmd.player->base->current_location.x;
	mmd.map_center_y = (int)mmd.player->base->current_location.y;
	mmd.map_radius = MINIMAP_SIZE / (2 * MINIMAP_CELL_SIZE);
	minimap_draw_cells(&mmd);
	minimap_draw_enemies(&mmd);
	minimap_draw_player(&mmd);
	minimap_bresenham_data_init(&mmd);
	minimap_draw_direction_line(&mmd);
}
