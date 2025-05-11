/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler_mouse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:51:35 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:51:54 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube.h>
#include <cube_input_handler.h>
#include <cube_mlx_handler.h>
#include <mlx.h>

t_mouse	input_handler_mouse_get_cursor_position(t_cube *cube)
{
	t_mouse			mouse;
	t_mlx_handler	*mlx_handler;

	mlx_handler = cube->mlx_handler;
	mlx_mouse_get_pos(mlx_handler->mlx, mlx_handler->mlx_win,
		&mouse.x, &mouse.y);
	return (mouse);
}

void	input_handler_mouse_reset_cursor_position(t_cube *cube)
{
	t_mlx_handler	*mlx_handler;

	mlx_handler = cube->mlx_handler;
	mlx_mouse_move(mlx_handler->mlx, mlx_handler->mlx_win,
		WINDOW_CENTER_X, WINDOW_CENTER_Y);
}
