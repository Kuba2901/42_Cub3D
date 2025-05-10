/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:43:20 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 19:44:42 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_drawing.h>
#include <cube_minimap.h>
#include <cube_entities.h>
#include <cube.h>
#include <cube_mlx_handler.h>

void	minimap_bresenham_data_init(t_minimap_data *mmd)
{
	mmd->bd.dir_length = MINIMAP_PLAYER_SIZE * 3;
	mmd->bd.dir_end_x = mmd->player_pos_x
		+ (int)(mmd->player->dir.dir_x * mmd->bd.dir_length);
	mmd->bd.dir_end_y = mmd->player_pos_y
		+ (int)(mmd->player->dir.dir_y * mmd->bd.dir_length);
	mmd->bd.dx = abs(mmd->bd.dir_end_x - mmd->player_pos_x);
	mmd->bd.dy = abs(mmd->bd.dir_end_y - mmd->player_pos_y);
	if (mmd->player_pos_x < mmd->bd.dir_end_x)
		mmd->bd.sx = 1;
	else
		mmd->bd.sx = -1;
	if (mmd->player_pos_y < mmd->bd.dir_end_y)
		mmd->bd.sy = 1;
	else
		mmd->bd.sy = -1;
	mmd->bd.err = mmd->bd.dx - mmd->bd.dy;
	mmd->bd.x = mmd->player_pos_x;
	mmd->bd.y = mmd->player_pos_y;
}

void	minimap_draw_direction_line(t_minimap_data *mmd)
{
	int	e2;

	while (TRUE)
	{
		if (mmd->bd.x >= mmd->minimap_pos_x
			&& mmd->bd.x < mmd->minimap_pos_x + MINIMAP_SIZE
			&& mmd->bd.y >= mmd->minimap_pos_y
			&& mmd->bd.y < mmd->minimap_pos_y + MINIMAP_SIZE)
			draw_my_mlx_pixel_put(mmd->img, mmd->bd.x, mmd->bd.y,
				MM_PLAYER_COLOR);
		if (mmd->bd.x == mmd->bd.dir_end_x && mmd->bd.y == mmd->bd.dir_end_y)
			break ;
		e2 = 2 * mmd->bd.err;
		if (e2 > -mmd->bd.dy)
		{
			mmd->bd.err -= mmd->bd.dy;
			mmd->bd.x += mmd->bd.sx;
		}
		if (e2 < mmd->bd.dx)
		{
			mmd->bd.err += mmd->bd.dx;
			mmd->bd.y += mmd->bd.sy;
		}
	}
}
