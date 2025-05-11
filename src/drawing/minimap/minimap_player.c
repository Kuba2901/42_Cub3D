/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 18:43:20 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 19:40:19 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_drawing.h>
#include <cube_minimap.h>
#include <cube_entities.h>
#include <cube.h>
#include <cube_mlx_handler.h>

void	minimap_draw_player(t_minimap_data *mmd)
{
	int	y;
	int	x;
	int	px;
	int	py;

	mmd->player_pos_x = mmd->minimap_pos_x + MINIMAP_SIZE / 2;
	mmd->player_pos_y = mmd->minimap_pos_y + MINIMAP_SIZE / 2;
	y = -MINIMAP_PLAYER_SIZE - 1;
	while (++y <= MINIMAP_PLAYER_SIZE)
	{
		x = -MINIMAP_PLAYER_SIZE - 1;
		while (++x <= MINIMAP_PLAYER_SIZE)
		{
			if (x * x + y * y <= MINIMAP_PLAYER_SIZE * MINIMAP_PLAYER_SIZE)
			{
				px = mmd->player_pos_x + x;
				py = mmd->player_pos_y + y;
				if (px >= mmd->minimap_pos_x
					&& px < mmd->minimap_pos_x + MINIMAP_SIZE
					&& py >= mmd->minimap_pos_y
					&& py < mmd->minimap_pos_y + MINIMAP_SIZE)
					draw_my_mlx_pixel_put(mmd->img, px, py, MM_PLAYER_COLOR);
			}
		}
	}
}
