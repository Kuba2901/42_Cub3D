/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 20:38:57 by jnenczak          #+#    #+#             */
/*   Updated: 2025/05/10 20:52:35 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cube_input_handler.h>
#include <cube.h>
#include <cube_entities.h>
#include <cube_runtime.h>
#include <cube_controls.h>

int	input_handler_mouse_movement(int x, int y, t_cube *cube)
{
	t_mouse				mouse;
	int					delta_x;
	double				r_speed;
	t_runtime_handler	*rh;

	(void)x;
	(void)y;
	if (!cube || !cube->runtime_handler)
		return (0);
	rh = cube->runtime_handler;
	rh->frametime = (rh->time - rh->old_time) / 1000.0;
	r_speed = cube->runtime_handler->frametime * 3.0;
	mouse = input_handler_mouse_get_cursor_position(cube);
	if (mouse.x == cube->input_handler->mouse.x)
		return (0);
	delta_x = mouse.x - cube->input_handler->mouse.x;
	if (delta_x < 0)
		handle_rotation_left(cube, r_speed);
	else
		handle_rotation_right(cube, r_speed);
	input_handler_mouse_reset_cursor_position(cube);
	return (0);
}
